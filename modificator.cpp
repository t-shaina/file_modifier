#include "modificator.h"
#include <QDir>

const static int number_of_bytes = 8;
const static int ascii_dec_A     = 65;
const static int ascii_dec_zero  = 48;

Modificator::Modificator(QList<QString> in_files,
                         QString in,
                         QString out,
                         bool rm_state,
                         bool rewrite_state,
                         QString var){
    in_files_       = new QList<QString>(in_files);
    in_dir_         = new QString(in);
    out_dir_        = new QString(out);
    rm_state_       = rm_state;
    rewrite_state_  = rewrite_state;
    var_            = new QString(var);
    qDebug() << "in Modificator ctor in files  is: " << in_files;
}

Modificator::~Modificator(){
    delete in_files_;
    delete in_dir_;
    delete out_dir_;
    delete var_;
}

void Modificator::modification(){
    bool have_open_files = false;
    QFile* current_file  = new QFile();
    for (int i = 0; i < in_files_->size(); i++){
        current_file->setFileName(in_files_->at(i));
        QDir::setCurrent(*in_dir_);
        if (!current_file->isOpen()) {
            QSharedPointer<QByteArray> data = file_modification(current_file);
            have_open_files = have_open_files  ||  !write_to_file(current_file, out_dir_, data);
            // если директории равны, при rm_state_ == rewrite_state_ == true
            // не удалять перезаписанный файл
            if(rm_state_ && !(*in_dir_ == *out_dir_))
                rm_file(current_file);
        }
        else
            have_open_files = have_open_files || true;
    }
    qDebug() << "in modif current  file open is " << current_file->isOpen() << " " <<  current_file->openMode();
    delete current_file;
    if (have_open_files) emit some_files_open();
}

QSharedPointer<QByteArray> Modificator::file_modification(QFile* file) const{
    QDir::setCurrent(*in_dir_);
    qDebug() << "in file modificator current dir: " << *in_dir_;
    if (!file->open(QIODeviceBase::ReadOnly))
        return nullptr;
    if (file->bytesAvailable() == 0)
        return nullptr;
    QSharedPointer<QByteArray> data = read_from_file(file);
    bool operation_state            = do_operation(data);
    file->close();
    return data;
}

QSharedPointer<QByteArray> Modificator::read_from_file(QFile* file) const{
    int zeroes_count = number_of_bytes - file->bytesAvailable();
    QByteArray* in   = new QByteArray(file->readAll());
    // дополнить массив старшими нулями
    in->insert(0, zeroes_count, '0');
    QSharedPointer<QByteArray> in_ptr (in);
    return in_ptr;
}

// считается, что входные данные представлены потоком байт, не строковым предсталением
// операция производится над всеми входными байтами
bool Modificator::do_operation(QSharedPointer<QByteArray> in_data) const{
    for (int i = 0, var_counter = 0; i < in_data->size(); i++, var_counter++){
        if (var_counter == 16) var_counter = 0;
        (*in_data)[i] = do_xor(in_data->at(i), var_->at(var_counter), var_->at(++var_counter));
    }
}

// два символа входной переменной-строки соответствуют одному байту переменной
char Modificator::do_xor(char inp, QChar var_first, QChar var_second) const{
    quint8 buf_var_first = char_to_int(var_first);
    quint8 var = buf_var_first << 4 | char_to_int(var_second);
    return inp ^ var;
}

quint8 Modificator::char_to_int(QChar symbol) const{
    symbol.toUpper();
    int ascii_dec = symbol.unicode();
    int counter   = 0;
    quint8 rez    = 0;
    if (ascii_dec >= ascii_dec_zero && ascii_dec < ascii_dec_zero + 10){
        counter += ascii_dec - ascii_dec_zero;
    }
    if (ascii_dec >= ascii_dec_A && ascii_dec < ascii_dec_A + 6){
        counter += ascii_dec - ascii_dec_A + 10;
    }
    for (int i = 0; i < counter; i++){
        rez = rez + 1;
    }
    return rez;
}

bool Modificator::write_to_file(const QFile* in_file, const QString* out_dir, const QSharedPointer<QByteArray> data) const{
    QDir::setCurrent(*out_dir_);
    QFile* out_file;
    bool is_exist   = is_file_name_exist(in_file->fileName(), out_dir);

    if (is_exist && !rewrite_state_){
        out_file = new QFile(choosing_valid_file_name_in_dir(in_file->fileName(), out_dir));
    }
    else out_file  = new QFile(in_file->fileName());

    if (rewrite_state_ &&
        (out_file->isOpen())){
        delete out_file;
        return 0;
    }   
    QDir::setCurrent(*out_dir_);

    if (is_exist && rewrite_state_){
        out_file->open(QIODeviceBase::WriteOnly | QIODeviceBase::ExistingOnly);
    }
    else {
        out_file->open(QIODeviceBase::WriteOnly | QIODeviceBase::NewOnly);
    }

    int bytes = out_file->write(*data);
    out_file->close();
    delete out_file;
    return bytes;
}

bool Modificator::rm_file(QFile* file) const{
    QDir::setCurrent(*in_dir_);
    return file->remove();//move to trash
}

QString Modificator::choosing_valid_file_name_in_dir(const QString file_name, const QString* dir) const{
    QString new_name = file_name;
    while (true){
        new_name = modification_out_file_name(new_name);
        if (!is_file_name_exist(new_name, dir)) break;
    }
    return new_name;
}

QString Modificator::modification_out_file_name(const QString file_name) const{
    QString new_name         = file_name;
    QString current_name     = file_name;
    int first_bracket_index  = current_name.lastIndexOf('(');
    int second_bracket_index = current_name.lastIndexOf(')');
    int point_index = current_name.lastIndexOf('.');
    // в имени файла уже есть полноценный порядковый номер
    // вида (N)
    if (first_bracket_index != -1 && second_bracket_index != -1) {
        int number         = current_name.sliced(first_bracket_index + 1, second_bracket_index - first_bracket_index - 1).toInt();
        new_name           = current_name.sliced(0, first_bracket_index);
        QString number_str = "()";
        number_str.insert(1, QString::number(++number));
        if (point_index != -1){
            QString format_str = current_name.sliced(point_index);
            number_str += format_str;
        }
        return new_name += number_str;
    }
    // добавление порядкового номера для файла без расширения

    if (point_index == -1) return new_name += "(1)";
    // добавление порядкового номера для файла с расширением
    return new_name.insert(point_index, "(1)");
}

bool Modificator::is_file_name_exist(const QString file_name, const QString* dir) const{
    QDir directory(*dir);
    qDebug() << " in is file name exist is: " << directory.exists(file_name);
    return directory.exists(file_name);
}


