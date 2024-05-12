#include "manager.h"
#include <QDir>

const static int sec_to_msec = 1000;

Manager::Manager(QObject *parent) {
    timer = new QTimer(parent);
    modificator = nullptr;
    connect(modificator, SIGNAL(these_files_open(const QList<QString>)), this, SLOT(files_open(const QList<QString>)));
    connect(timer, SIGNAL(timeout()), this, SLOT(working()));
}

Manager::~Manager(){
    delete timer;
    delete modificator;
}

void Manager::processing(const Current_settings* setting){
    modificator = new Modificator(apply_mask(setting->in_directory_, setting->mask_),
                                  adding_slash(setting->in_directory_),
                                  adding_slash(setting->out_directory_),
                                  setting->is_removable_,
                                  setting->is_rewrite_,
                                  setting->var_->toLocal8Bit());
    timer->setInterval(setting->interval_sec_ * sec_to_msec);
    working();
}

void Manager::working(){
    modificator->modification();
}

QList<QString> Manager::apply_mask(QString* in_dir, QString* mask) const{
    QStringList rez;
    QList<QString> masks;
    masks.push_back(*mask);
    QDir dir(*in_dir);
    rez = dir.entryList(masks);
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

void Manager::files_open(const QList<QString> files) {
    emit has_problem_with_files(files);
}

