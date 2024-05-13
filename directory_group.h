#ifndef DIRECTORY_GROUP_H
#define DIRECTORY_GROUP_H

#include "dialog.h"

#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>

class Directory_group : public QGroupBox{

    Q_OBJECT

public:

    Directory_group(QWidget* parent = nullptr, int width = 50, int height = 30);
    ~Directory_group();
    Directory_group(Directory_group const& other)            = delete;
    Directory_group& operator=(Directory_group const& other) = delete;
    Directory_group(Directory_group && other)                = delete;
    Directory_group& operator=(Directory_group && other)     = delete;
    QString get_dir() const;

private:

    QHBoxLayout* layout;
    QPushButton* button;
    QLineEdit* edit;
    Dialog* dialog;

private slots:

    void create_file_system_dialog();
    void set_edit(QString);
    void destroy_dialog();
    void dialog_finished(int);
};

#endif // DIRECTORY_GROUP_H
