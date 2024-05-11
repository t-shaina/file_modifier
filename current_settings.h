#ifndef CURRENT_SETTINGS_H
#define CURRENT_SETTINGS_H

#include <QString>
#include <QVector>

class Current_settings{

public:
    QString* in_directory_;
    QString* mask_;
    QString* out_directory_;
    bool is_removable_;
    bool is_rewrite_;
    int interval_sec_;
    QVector<bool>* var_;

    Current_settings(QString in_directory,
                     QString mask,
                     QString out_directory,
                     bool is_removable,
                     bool is_rewrite,
                     int interval,
                     QString var_);
    ~Current_settings();
    Current_settings(Current_settings const& other)            = delete;
    Current_settings& operator=(Current_settings const& other) = delete;
    Current_settings(Current_settings && other)                = delete;
    Current_settings& operator=(Current_settings && other)     = delete;

private:
    QVector<bool> str_to_vec(const QString str);
};

#endif // CURRENT_SETTINGS_H
