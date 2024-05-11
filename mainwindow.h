#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "current_settings.h"
#include "graphics.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

    Graphics* graphics;

public:

    MainWindow(QApplication* parent = nullptr);
    ~MainWindow();
    MainWindow(MainWindow const& other)        = delete;
    MainWindow& other(MainWindow const& other) = delete;
    MainWindow(MainWindow && other)            = delete;
    MainWindow& other(MainWindow && other)     = delete;
    Current_settings* settings;

public slots:

    void on_settings_ready();
    void on_has_problem_with_files(const QList<QString>);

signals:

    void form_worked(const Current_settings*);

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
