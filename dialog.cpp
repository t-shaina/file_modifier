#include "dialog.h"

#include <Qlabel>
#include <QPushButton>
#include <QHBoxLayout>

const static int dialog_window_width          = 500;
const static int dialog_window_height         = 350;
const static int horizontal_spacing           = 10;
const static int buttons_spacing              = 10;
const static QString cancel_button_text       = "Отменить";
const static QString ok_button_text           = "ОK";
const static int buttons_height               = 30;
const static int buttons_width                = 90;
const static int file_system_view_height      = 280;
const static QString file_system_window_title = " Выбор каталога";

Dialog::Dialog(QWidget* parent)
    : QDialog(parent, Qt::Dialog)
    , main_layout(new QVBoxLayout(this)){
    buttons_layout   = new QHBoxLayout(this);
    buttons_group    = new QGroupBox(this);
    file_system_view = new QTreeView(this);
    model            = new QFileSystemModel(this);
    cancel_button    = new QPushButton(cancel_button_text, this);
    ok_button        = new QPushButton(ok_button_text, this);

    this->setFixedSize(dialog_window_width, dialog_window_height);
    create_file_system_dialog();
    main_layout->setSpacing(horizontal_spacing);
    this->show();
    this->setModal(true);
    this->setLayout(main_layout);
    connect(this, SIGNAL(finished(int)), this, SLOT(on_dialog_finished(int)));
    connect(cancel_button, SIGNAL(clicked()), this, SLOT(on_cancel_button_clicked()));
    connect(ok_button, SIGNAL(clicked()), this, SLOT(on_ok_button_clicked()));
}

void Dialog::create_file_system_dialog(){

    main_layout->addWidget(file_system_view, Qt::AlignHCenter | Qt::AlignVCenter);
    model->setRootPath(QDir::rootPath());
    file_system_view->setModel(model);
    file_system_view->setRootIndex(model->index(QDir::rootPath()));
    file_system_view->setFixedHeight(file_system_view_height);

    cancel_button->setFixedSize(QSize(buttons_width, buttons_height));
    ok_button->setFixedSize(QSize(buttons_width, buttons_height));
    buttons_layout->addWidget(cancel_button, Qt::AlignCenter);
    buttons_layout->addWidget(ok_button, Qt::AlignCenter);
    buttons_layout->setSpacing(buttons_spacing);
    buttons_group->setLayout(buttons_layout);
    buttons_group->setStyleSheet("QGroupBox{border: 0px;}");
    main_layout->addWidget(buttons_group, Qt::AlignHCenter | Qt::AlignVCenter);

    this->setWindowTitle(file_system_window_title);
}

Dialog::~Dialog(){
    delete main_layout;
    delete cancel_button;
    delete ok_button;
    delete buttons_layout;
    delete buttons_group;
    delete file_system_view;
    delete model;
}

void Dialog::on_cancel_button_clicked(){
    emit cancel_button_selected();
}

void Dialog::on_ok_button_clicked(){
    QItemSelectionModel* select_model = file_system_view->selectionModel();
    QModelIndex index                 = select_model->currentIndex();
    QFileSystemModel* model           = static_cast<QFileSystemModel*>( file_system_view->model());
    const QString path                = model->filePath(index);
    emit directory_selected(path);
}

void Dialog::on_dialog_finished(int code){
    emit dialog_finished(code);
}
