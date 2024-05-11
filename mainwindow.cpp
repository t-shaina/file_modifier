#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFont>

const static int window_width    = 960;
const static int window_height   = 540;
const static QString window_font = "Cochin";

MainWindow::MainWindow(QApplication* parent)
    : QMainWindow()
    , ui(new Ui::MainWindow)
    , graphics(new Graphics(this, window_width, window_height)){
    ui->setupUi(this);
    this->setFixedSize(window_width, window_height);
    QFont main_window_font(window_font, 0, 0);
    this->setFont(main_window_font);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setEnabled(true);
    settings = nullptr;
    connect(graphics, SIGNAL(settings_ready()), this, SLOT(on_settings_ready()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete graphics;
    delete settings;
}

void MainWindow::on_settings_ready(){
    settings = new Current_settings(graphics->get_in_dir(),
                                    graphics->get_mask(),
                                    graphics->get_out_dir(),
                                    graphics->get_rm_state(),
                                    graphics->get_rewrite_state(),
                                    graphics->get_interval_sec(),
                                    graphics->get_var());
    emit form_worked(settings);
}

void MainWindow::on_has_problem_with_files(const QList<QString> files){
    Dialog msg(this, false, files);
}
