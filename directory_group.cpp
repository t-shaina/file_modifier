#include "directory_group.h"

#include <QHBoxLayout>
#include <QDir>
#include <QSharedPointer>

const static QString button_text     = "Просмотр";
const static int buttons_width       = 90;
const static int horizontal_spacing  = 15;
const static int l_dir_group_margin  = 0;
const static int t_dir_group_margin  = 0;
const static int r_dir_group_margin  = 0;
const static int b_dir_group_margin  = 0;

Directory_group::Directory_group(QWidget* parent, int width, int height)
    :QGroupBox(parent){
    layout = new QHBoxLayout(this);
    button = new QPushButton(button_text, this);
    edit   = new QLineEdit(QDir::rootPath(), this);
    dialog = nullptr;
    button->setFixedSize(QSize(buttons_width, height));
    edit->setFixedHeight(height);
    edit->setFixedWidth(width - horizontal_spacing - buttons_width);
    layout->addWidget(edit, Qt::AlignLeft    | Qt::AlignJustify);
    layout->addWidget(button, Qt::AlignRight | Qt::AlignJustify);
    layout->setSpacing(horizontal_spacing);
    this->setContentsMargins(l_dir_group_margin, t_dir_group_margin, r_dir_group_margin, b_dir_group_margin);
    this->setLayout(layout);
    connect(button, SIGNAL(clicked()), this, SLOT(create_file_system_dialog()));
}

Directory_group::~Directory_group(){
    delete layout;
    delete button;
    delete edit;
}

void Directory_group::create_file_system_dialog(){
    delete dialog;
    dialog = new Dialog(this);
    connect(dialog, SIGNAL(directory_selected(QString)), this, SLOT(set_edit(QString)));
    connect(dialog, SIGNAL(cancel_button_selected()), this, SLOT(destroy_dialog()));
    connect(dialog, SIGNAL(dialog_finished(int)), this, SLOT(dialog_finished(int)));
}

void Directory_group::set_edit(QString text){
    edit->setText(text);
    delete dialog;
}

void Directory_group::destroy_dialog(){
    delete dialog;
}

void Directory_group::dialog_finished(int){
    // do something
}

QString Directory_group::get_dir() const{
    return edit->text();
}

