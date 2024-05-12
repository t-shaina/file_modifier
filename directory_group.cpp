#include "directory_group.h"

#include <QHBoxLayout>
#include <QDir>

const static QString button_text     = "Просмотр";
const static int buttons_width       = 90;
const static int buttons_height      = 30;
const static int horizontal_spacing  = 15;
const static int l_dir_group_margin  = 0;
const static int t_dir_group_margin  = 0;
const static int r_dir_group_margin  = 0;
const static int b_dir_group_margin  = 0;

Directory_group::Directory_group(QWidget* parent, int width, int height)
    :QGroupBox(parent){
    QHBoxLayout* layout = new QHBoxLayout(this);
    button              = new QPushButton(button_text, this);
    edit                = new QLineEdit(QDir::rootPath(), this);
    dialog              = nullptr;
    button->setFixedSize(QSize(buttons_width, buttons_height));
    edit->setFixedHeight(buttons_height);
    edit->setFixedWidth(width - horizontal_spacing - buttons_width - l_dir_group_margin - r_dir_group_margin);
    layout->addWidget(edit, Qt::AlignLeft | Qt::AlignJustify);
    layout->addWidget(button, Qt::AlignRight | Qt::AlignJustify);
    layout->setSpacing(horizontal_spacing);
    //this->setContentsMargins(l_dir_group_margin, t_dir_group_margin, r_dir_group_margin, b_dir_group_margin);
    this->setLayout(layout);
    this->setFixedSize(QSize(width, height));


}

Directory_group::~Directory_group(){
    delete button;
    delete edit;
    delete dialog;
}

void Directory_group::create_file_system_dialog(){
    dialog = new Dialog(this, true);
}

void Directory_group::set_edit(QString text){
    edit->setText(text);
}

void Directory_group::destroy_dialog(){
    delete dialog;
}

void Directory_group::on_dialog_finished(int){
    dialog = nullptr; //рассмотреть
}

QString Directory_group::get_dir() const{
    return edit->text();
}

QPushButton* Directory_group::get_button() const{
    return button;
}

Dialog* Directory_group::get_dialog() const{
    return dialog;
}

QLineEdit* Directory_group::get_edit() const{
    return edit;
}
