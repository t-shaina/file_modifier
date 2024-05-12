#include "modificator.h"
#include <QDir>

const static int number_of_bytes = 8;

Modificator::Modificator(QList<QString> in_files,
                         QString in,
                         QString out,
                         bool rm_state,
                         bool rewrite_state,
                         QByteArray var){
    in_files_       = new QList<QString>(in_files);
    in_dir_         = new QDir(in);
    out_dir_        = new QDir(out);
    rm_state_       = rm_state;
    rewrite_state_  = rewrite_state;
    var_            = new QByteArray(var);
}

Modificator::~Modificator(){
    delete in_files_;
    delete in_dir_;
    delete out_dir_;
    delete var_;
}

int Modificator::modification(){
    QList<QString> open_files;
    QFile* current_file = new QFile();
    for (int i = 0; i < in_files_->size(); i++){
        current_file->setFileName(in_files_->at(i));
        QDir::setCurrent(in_dir_->dirName());
        if (current_file->isOpen()) {
            open_files.push_back(in_files_->at(i));
        }
        else {
            QSharedPointer<QByteArray> data = modification(current_file);
            write_to_file(current_file, out_dir_, data);
            if(rm_state_) rm_file(current_file);
        }
    }
    delete current_file;
    emit these_files_open(open_files);
    return 1;
}

QSharedPointer<QByteArray> Modificator::modification(QFile* file) const{
    if (!file->open(QIODeviceBase::ReadOnly)) return nullptr;
    if (file->bytesAvailable() == 0) return nullptr;
    QSharedPointer<QByteArray> data = read_from_file(file);
    bool operation_state            = do_operation(data);
    file->close();
    return data;
}

QSharedPointer<QByteArray> Modificator::read_from_file(QFile* file) const{
    int zeroes_count = number_of_bytes - file->bytesAvailable();
    QByteArray* in   = new QByteArray(file->readAll());
    in->insert(0, zeroes_count, '0');
    const QSharedPointer<QByteArray> in_ptr (in);
    return in_ptr;
}

bool Modificator::do_operation(QSharedPointer<QByteArray> in_data) const{
    for (int i = 0; i < number_of_bytes; i++){
        (*in_data)[i] = do_xor(in_data->at(i), var_->at(i));
    }

}

char Modificator::do_xor(char first, char second) const{
    return first ^ second;
}

bool Modificator::write_to_file(const QFile* in_file, const QDir* out_dir, const QSharedPointer<QByteArray> data) const{
    QString out_file_name;
    QDir::setCurrent(out_dir_->dirName());
    bool is_exist = is_file_name_exist(in_file, out_dir);
    if (is_exist && !rewrite_state_) out_file_name = modification_out_file_name(in_file);
    else out_file_name = in_file->fileName();
    QFile* out_file    = new QFile(out_file_name);
    if (rewrite_state_) {
        if (out_file->isOpen()){
            delete out_file;
            return 0;
        }
    }
    if (is_exist) out_file->open(QIODeviceBase::WriteOnly | QIODeviceBase::ExistingOnly);
    else out_file->open(QIODeviceBase::WriteOnly | QIODeviceBase::NewOnly);
    int bytes = out_file->write(*data);
    out_file->close();
    delete out_file;
    return bytes;
}

bool Modificator::rm_file(QFile* file) const{
    return file->remove();//move to trash
}

QString Modificator::modification_out_file_name(const QFile* file) const{
    // только для файлов, имеющих расширение
    QString current_name     = file->fileName();
    QString new_name         = current_name;
    int first_bracket_index  = current_name.lastIndexOf('(');
    int second_bracket_index = current_name.lastIndexOf(')');
    if (first_bracket_index != -1 && second_bracket_index != -1) {
        int number = new_name.sliced(first_bracket_index + 1, second_bracket_index - first_bracket_index - 1).toInt();
        QString number_str = "()";
        number_str.insert(1, QString::number(++number));
        return new_name.insert(first_bracket_index + 1, number_str);
    }
    return new_name.insert(first_bracket_index + 1, "(1)");
}

bool Modificator::is_file_name_exist(const QFile* file, const QDir* dir) const{
    return dir->exists(file->fileName());
}
