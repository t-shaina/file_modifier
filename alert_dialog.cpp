#include "alert_dialog.h"

const int max_count_of_files                  = 10;
const static int dialog_window_width          = 400;
const static int dialog_window_height         = 150;
const static int horizontal_spacing           = 10;
const static QString ok_button_text           = "ОK";
const static int buttons_height               = 30;
const static int buttons_width                = 90;
const static QString alert_message_text       = "Некоторые файлы открыты и не могут быть обработаны ";
const static QString alert_window_title       = " Проблема";


Alert_dialog::Alert_dialog(QWidget* parent, const QList<QString> files)
    : QDialog(parent, Qt::Dialog)
    , main_layout(new QVBoxLayout(this)){
    this->setFixedSize(dialog_window_width, dialog_window_height);
    main_layout->setSpacing(horizontal_spacing);
    QString msg   = alert_message_text;
    int count     = files.size() < max_count_of_files ? files.size() : max_count_of_files;
    for (int i = 0; i < count; ++i){
        msg += ' ';
        msg += files.at(i);
    }
    QLabel* alert_label          = new QLabel(msg, this);
    QPushButton* ok_alert_button = new QPushButton(ok_button_text, this);
    ok_alert_button->setFixedSize(QSize(buttons_width, buttons_height));
    main_layout->addWidget(alert_label, Qt::AlignVCenter);
    main_layout->addWidget(ok_alert_button, Qt::AlignVCenter);
    this->setWindowTitle(alert_window_title);
    alert_label->setWordWrap(true);
    connect(ok_alert_button, SIGNAL(clicked()), this, SLOT(on_ok_alert_button_clicked()));
    connect(this, SIGNAL(finished(int)), this, SLOT(dialog_finished(int)));
    this->show();
    this->setModal(true);

}

Alert_dialog::~Alert_dialog(){
    delete main_layout;
    //
    //delete alert_label;
    //delete ok_alert_button;
}

void Alert_dialog::on_ok_alert_button_clicked(){
    emit ok_alert_button_selected();
}

void Alert_dialog::dialog_finished(int code){
    emit alert_dialog_finished(code);
}
