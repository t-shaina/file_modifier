#include "dialog.h"

#include <Qlabel>
#include <QPushButton>
#include <QFileSystemModel>
#include <QGroupBox>
#include <QHBoxLayout>

const static int dialog_window_width          = 500;
const static int dialog_window_height         = 350;
const static int vertical_spacing             = 10;
const static int horizontal_spacing           = 10;
const static int buttons_spacing              = 10;
const static QString cancel_button_text       = "Отменить";
const static QString ok_button_text           = "ОK";
const static int buttons_height               = 30;
const static int buttons_width                = 90;
const static int file_system_view_height      = 280;
const static QString alert_message_text       = "Эти файлы открыты и не могут быть обработаны: ";
const static QString alert_window_title       = " Проблема";
const static QString file_system_window_title = " Выбор каталога";

Dialog::Dialog(QWidget* parent, bool is_file_system_dialog, const QList<QString> files)
    : QDialog(parent, Qt::Dialog)
    , main_layout(new QVBoxLayout(this)){
    file_system_view = nullptr;
    this->setFixedSize(dialog_window_width, dialog_window_height);
    is_file_system_dialog ? create_file_system_dialog() : create_alert_dialog(files);
    main_layout->setSpacing(horizontal_spacing);
    this->show();
    this->setModal(true);
    connect(this, SIGNAL(finished(int)), this, SLOT(on_dialog_finished(int)));
}

void Dialog::create_file_system_dialog(){
    file_system_view            = new QTreeView(this);
    QFileSystemModel* model     = new QFileSystemModel(this);
    QPushButton* cancel_button  = new QPushButton(cancel_button_text, this);
    QPushButton* ok_button      = new QPushButton(ok_button_text, this);
    QGroupBox* buttons_group    = new QGroupBox(this);
    QHBoxLayout* buttons_layout = new QHBoxLayout(this);

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

    connect(cancel_button, SIGNAL(clicked()), this, SLOT(on_cancel_button_clicked()));
    connect(ok_button, SIGNAL(clicked()), this, SLOT(on_ok_button_clicked()));
    connect(this, SIGNAL(directory_selected(QString)), this->parent(), SLOT(set_edit(QString)));
    connect(this, SIGNAL(cancel_button_selected()), this->parent(), SLOT(destroy_dialog()));
    connect(this, SIGNAL(dialog_finished(int)), this->parent(), SLOT(on_dialog_finished(int)));
}

Dialog::~Dialog(){
    delete  main_layout;
    delete file_system_view;
}

void Dialog::create_alert_dialog(const QList<QString> files){
    QString msg   = alert_message_text;
    int max_count =  20;
    int count     = files.size() < max_count ? files.size() : max_count;
    for (int i = 0; i < count; ++i){
        msg += ' ';
        msg += files.at(i);
    }
    QLabel* alert_label          = new QLabel(alert_message_text, this);
    QPushButton* ok_alert_button = new QPushButton(ok_button_text, this);
    ok_alert_button->setFixedSize(QSize(buttons_width, buttons_height));
    main_layout->addWidget(alert_label, Qt::AlignHCenter | Qt::AlignVCenter);
    main_layout->addWidget(ok_alert_button, Qt::AlignRight | Qt::AlignVCenter);
    this->setWindowTitle(alert_window_title);

    connect(ok_alert_button, SIGNAL(clicked()), this, SLOT(on_ok_button_clicked()));
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

void Dialog::on_ok_alert_button_clicked(){
    emit ok_alert_button_selected();
}

void Dialog::on_dialog_finished(int code){
    emit dialog_finished(code);
}
