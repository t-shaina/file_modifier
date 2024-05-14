#include "manager.h"
#include <QDir>
#include <QRegularExpression>

const static int sec_to_msec = 1000;

Manager::Manager(QObject *parent) {
    timer       = new QTimer(parent);
    modificator = nullptr;
    connect(timer, SIGNAL(timeout()), this, SLOT(working()));
}

Manager::~Manager(){
    delete timer;
    delete modificator;
}

void Manager::processing(const Current_settings* setting){
    modificator = new Modificator(apply_mask(setting->in_directory_, setting->mask_),
                                  *setting->in_directory_,
                                  *setting->out_directory_,
                                  setting->is_removable_,
                                  setting->is_rewrite_,
                                  *setting->var_);
    connect(modificator, SIGNAL(some_files_open()), this, SLOT(files_open()));
    qDebug() << "in processing intervsl_sec is " << setting->interval_sec_ ;
    if (setting->interval_sec_ != 0){
        timer->setInterval(setting->interval_sec_ * sec_to_msec);
        timer->start();
    }
    working();

}

void Manager::working(){
    modificator->modification();
}

QList<QString> Manager::apply_mask(QString* in_dir, QString* mask) const{
    QStringList rez;
    //  mask может состоять более чем из одной маски
    //  тогда маски при вводе отделяются любым количеством пробелов и одной запятой
    QList<QString> masks = mask->split(QRegularExpression("[\\s{0,},{0,}\\s{0,}]"), Qt::SkipEmptyParts);
    //  пользователь может вводить маски формата  .cpp или *.cpp
    //  знак  '*' в случае подобного пользовательского ввода: "a*a.cpp"
    //  не будет означать произвольное количество символов
    for (auto i = masks.begin(); i != masks.end(); ++i){
        int point_index = i->lastIndexOf('.', 0);
        qDebug() << point_index;
        if (point_index == -1) continue;
        if (point_index == 0) i->insert(point_index, '*');
    }
    QDir dir(*in_dir);
    if (!mask->isEmpty()) rez = dir.entryList(masks, QDir::Files | QDir::Readable);
    else rez = dir.entryList(QDir::Files | QDir::Readable);
    return rez;
}

QString Manager::adding_slash(QString* dir) const{
    QString rez_dir;
    int offset = 0;
    for (int i = 0; i < dir->size(); ++i){
        int index = dir->indexOf('\\', offset++);
        if (index == -1) break;
        rez_dir += dir->at(i);
        if (index == i){
            rez_dir += '\\';
        }
    }
    return rez_dir;
}

void Manager::files_open() {
    emit has_problem_with_files();
}

