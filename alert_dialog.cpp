#include "alert_dialog.h"

const static int dialog_window_width          = 500;
const static int dialog_window_height         = 350;
const static int horizontal_spacing           = 10;
const static QString ok_button_text           = "ОK";
const static int buttons_height               = 30;
const static int buttons_width                = 90;
const static QString alert_message_text       = "Эти файлы открыты и не могут быть обработаны: ";
const static QString alert_window_title       = " Проблема";


Alert_dialog::Alert_dialog(QWidget* parent, const QList<QString> files)
    : QDialog(parent, Qt::Dialog)
    , main_layout(new QVBoxLayout(this)){
    this->setFixedSize(dialog_window_width, dialog_window_height);
    main_layout->setSpacing(horizontal_spacing);
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
    main_layout->addWidget(alert_label, Qt::AlignHCenter   | Qt::AlignVCenter);
    main_layout->addWidget(ok_alert_button, Qt::AlignRight | Qt::AlignVCenter);
    this->setWindowTitle(alert_window_title);

    connect(ok_alert_button, SIGNAL(clicked()), this, SLOT(on_ok_alert_button_clicked()));
    connect(this, SIGNAL(finished(int)), this, SLOT(dialog_finished(int)));
    this->show();
    this->setModal(true);

}

Alert_dialog::~Alert_dialog(){
    delete alert_label;
    delete ok_alert_button;
    delete main_layout;    
}

void Alert_dialog::on_ok_alert_button_clicked(){
    emit ok_alert_button_selected();
}

void Alert_dialog::dialog_finished(int code){
    emit alert_dialog_finished(code);
}
