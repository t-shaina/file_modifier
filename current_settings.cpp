#include "current_settings.h"

Current_settings::Current_settings(QString in_directory,
                                   QString mask,
                                   QString out_directory,
                                   bool is_removable,
                                   bool is_rewrite,
                                   int interval_sec,
                                   QString var){
    in_directory_  = new QString(in_directory);
    mask_          = new QString(mask);
    out_directory_ = new QString(out_directory);
    is_removable_  = is_removable;
    is_rewrite_    = is_rewrite;
    interval_sec_  = interval_sec;
    var_           = new QVector<bool>(str_to_vec(var));
}

Current_settings::~Current_settings(){
    delete in_directory_;
    delete mask_;
    delete out_directory_;
    delete var_;
}

QVector<bool> Current_settings::str_to_vec(QString str){
    return QVector<bool>();
}
