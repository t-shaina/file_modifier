#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFont>

const static int window_width    = 960;
const static int window_height   = 540;
const static QString window_font = "Cochin";

MainWindow::MainWindow(QApplication* parent)
    :/* QMainWindow(parent)
    ,*/ ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setFixedSize(window_width, window_height);
    QFont main_window_font(window_font, 0, 0);
    this->setFont(main_window_font);
    this->setAttribute(Qt::WA_DeleteOnClose);
    graphics = new Graphics(this, window_width, window_height);
    settings = nullptr;
    msg      = nullptr;
    connect(graphics, SIGNAL(settings_ready()), this, SLOT(keep_settings()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete graphics;
    delete settings;
    delete msg;
}

void MainWindow::keep_settings(){
    settings = new Current_settings(graphics->get_in_dir(),
                                    graphics->get_mask(),
                                    graphics->get_out_dir(),
                                    graphics->get_rm_state(),
                                    graphics->get_rewrite_state(),
                                    graphics->get_interval_sec(),
                                    graphics->get_var());
    emit form_worked(settings);
}

void MainWindow::problem_with_files(const QList<QString> files){
    msg = new Alert_dialog(this, files);
    connect(msg, SIGNAL(ok_alert_button_selected()), this, SLOT(alert_msg_delivered()));
    connect(msg, SIGNAL(alert_dialog_finished(int)), this, SLOT(dialog_finished(int)));
}

void MainWindow::alert_msg_delivered(){
    // do something
}

void MainWindow::dialog_finished(int){
    // do something
}
