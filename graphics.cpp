#include "graphics.h"

#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QStandardItemModel>

const static int number_of_bytes                      = 8;
const static int ascii_diff_between_uppercase_letters = 55;
const static int ascii_diff_between_lowercase_letters = 87;
const static int but_height = 30;
const static int but_width  = 90;
const static int l_margin   = 150;
const static int t_margin   = 30;
const static int r_margin   = 150;
const static int b_margin   = 30;
const static int rows_count = 8;
const static int v_spacing  = 10;
const static int h_spacing  = 30;
const static int right_column_width = 300;
const static int label_height       = 30;
const static QString window_title       = "Модификатор файлов";
const static QString in_dir_label_text  = "Выберите каталог входных файлов";
const static QString mask_label_text    = "Выберите маску входных файлов";
const static QString out_dir_label_text = "Выберите каталог выходных файлов";
const static QString rm_check_box_text  = "Удалить входные файлы";
const static QString action_label_text  = "При повторении имени выходного файла";
const static QString timer_label_text   = "Выберите периодичность срабатывания таймера";
const static QString var_label_text     = "Введите hex-значение переменной";
const static QString accept_button_text = "Применить";
const static QStringList action_combo_box_list = QStringList() << "Перезаписать файлы"
                                                               << "Модифицировать названия файлов";
const static QStringList timer_combo_box_list  = QStringList() << "0 секунд (таймер отключён)"
                                                               << "1 секунда"
                                                               << "5 секунд"
                                                               << "10 секунд";

Graphics::Graphics(QWidget* parent, int width, int height)
    : QWidget(parent)
    , in_dir_group    (new Directory_group(this, right_column_width, label_height))
    , mask_edit       (new QLineEdit(this))
    , out_dir_group   (new Directory_group(this, right_column_width, label_height))
    , rm_check_box    (new QCheckBox(rm_check_box_text, this))
    , action_combo_box(new QComboBox(this))
    , timer_combo_box (new QComboBox(this))
    , var_edit        (new QLineEdit(this))
    , accept_button   (new QPushButton(accept_button_text, this))
    , layout          (new QGridLayout(this)){

    QLabel* in_dir_label  = new QLabel(in_dir_label_text, this);
    QLabel* mask_label    = new QLabel(mask_label_text, this);
    QLabel* out_dir_label = new QLabel(out_dir_label_text, this);
    QLabel* action_label  = new QLabel(action_label_text, this);
    QLabel* timer_label   = new QLabel(timer_label_text, this);
    QLabel* var_label     = new QLabel(var_label_text, this);

    layout->addWidget(in_dir_label, 0, 0, Qt::AlignLeft       | Qt::AlignTop);
    layout->addWidget(in_dir_group, 0, 1, Qt::AlignCenter     | Qt::AlignTop);
    layout->addWidget(mask_label, 1, 0, Qt::AlignLeft         | Qt::AlignTop);
    layout->addWidget(mask_edit, 1, 1, Qt::AlignCenter        | Qt::AlignTop);
    layout->addWidget(out_dir_label, 2, 0, Qt::AlignLeft      | Qt::AlignTop);
    layout->addWidget(out_dir_group, 2, 1, Qt::AlignCenter     | Qt::AlignTop);
    layout->addWidget(rm_check_box, 3, 1, Qt::AlignCenter     | Qt::AlignTop);
    layout->addWidget(action_label, 4, 0, Qt::AlignLeft       | Qt::AlignTop);
    layout->addWidget(action_combo_box, 4, 1, Qt::AlignCenter | Qt::AlignTop);
    layout->addWidget(timer_label, 5, 0, Qt::AlignLeft        | Qt::AlignTop);
    layout->addWidget(timer_combo_box, 5, 1, Qt::AlignCenter  | Qt::AlignTop);
    layout->addWidget(var_label, 6, 0, Qt::AlignLeft          | Qt::AlignTop);
    layout->addWidget(var_edit, 6, 1, Qt::AlignCenter         | Qt::AlignTop);
    layout->addWidget(accept_button, 7, 1, Qt::AlignCenter    | Qt::AlignTop);

    this->setContentsMargins(l_margin, t_margin, r_margin, b_margin);
    this->setFixedSize(width, height);
    layout->setVerticalSpacing(v_spacing);
    layout->setHorizontalSpacing(h_spacing);
    layout->setColumnMinimumWidth(0, width / 2);
    for (int i = 0; i < rows_count; i++){
        layout->setRowMinimumHeight(i, (height - t_margin - b_margin - (rows_count - 1) * v_spacing) / rows_count);
    }

    setting_combo_boxes();
    setting_edits();
    setting_button();
    this->setWindowTitle(window_title);
    this->setLayout(layout);
    this->show();

    connect(accept_button, SIGNAL(clicked()), this, SLOT(on_accept_button_clicked()));
    connect(in_dir_group->get_button(), SIGNAL(clicked()), in_dir_group, SLOT(create_file_system_dialog()));
    connect(out_dir_group->get_button(), SIGNAL(clicked()), out_dir_group, SLOT(create_file_system_dialog()));
    connect(in_dir_group->get_dialog(), SIGNAL(directory_selected(QString)), in_dir_group, SLOT(set_edit(QString)));
    connect(out_dir_group->get_dialog(), SIGNAL(directory_selected(QString)), out_dir_group, SLOT(set_edit(QString)));
    connect(in_dir_group->get_dialog(), SIGNAL(cancel_button_selected()), this, SLOT(destroy_dialog()));
    //connect(dialog, SIGNAL(dialog_finished(int)), this, SLOT(on_dialog_finished(int)));
}

Graphics::~Graphics(){
    delete in_dir_group;
    delete mask_edit;
    delete out_dir_group;
    delete rm_check_box;
    delete action_combo_box;
    delete timer_combo_box;
    delete var_edit;
    delete accept_button;
    delete layout;
}

void Graphics::setting_combo_boxes(bool is_default_setting){
    QStandardItemModel* action_model = new QStandardItemModel(action_combo_box);
    QStandardItemModel* timer_model  = new QStandardItemModel(timer_combo_box);
    action_combo_box->setModel(action_model);
    timer_combo_box->setModel(timer_model);
    action_combo_box->addItems(action_combo_box_list);
    timer_combo_box->addItems(timer_combo_box_list);
    action_combo_box->setFixedSize(right_column_width, label_height);
    timer_combo_box->setFixedSize(right_column_width, label_height);
    action_combo_box->setEnabled(is_default_setting);
    timer_combo_box->setEnabled(is_default_setting);
}

void Graphics::setting_edits(bool is_default_setting){
    mask_edit->setFixedSize(right_column_width, label_height);
    var_edit->setFixedSize(right_column_width, label_height);
    mask_edit->setEnabled(is_default_setting);
    var_edit->setEnabled(is_default_setting);
    mask_edit->setModified(is_default_setting);
    var_edit->setModified(is_default_setting);
    mask_edit->setReadOnly(!is_default_setting);
    var_edit->setReadOnly(!is_default_setting);
}

void Graphics::setting_button(bool is_default_setting){
    accept_button->setFixedSize(but_width, but_height);
    accept_button->setEnabled(is_default_setting);
}

void Graphics::settingg_check_box(bool is_default_setting){
    rm_check_box->setCheckable(true);
}


void Graphics::on_accept_button_clicked(){
    emit settings_ready();
}

QString Graphics::get_in_dir() const{
    return in_dir_group->get_dir();
}

QString Graphics::get_mask() const{
    return mask_edit->text();
}

QString Graphics::get_out_dir() const{
    return out_dir_group->get_dir();
}

bool Graphics::get_rm_state() const{
    return rm_check_box->isChecked();
}

bool Graphics::get_rewrite_state() const{
    if (action_combo_box->placeholderText().contains("Перезаписать", Qt::CaseInsensitive))
        return true;
    return false;
}

int Graphics::get_interval_sec() const{
    int space_index = timer_combo_box->placeholderText().indexOf(" "); // \\s
    return  timer_combo_box->placeholderText().sliced(0, space_index - 1).toInt();
}

QString Graphics::get_var() const{
    QString var     = var_edit->placeholderText().toUpper();
    int zeros_count = number_of_bytes - var.size();
    for (int i = 0; i < zeros_count; i++)
        var.insert(0, '0');
    return var;
}
