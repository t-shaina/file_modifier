#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QGroupBox>

class Dialog : public QDialog{

    Q_OBJECT

public:

    Dialog(QWidget* parent = nullptr);
    ~Dialog();
    Dialog(Dialog const& other)             = delete;
    Dialog& operator=(Dialog const& other)  = delete;
    Dialog(Dialog && other)                 = delete;
    Dialog& operator=(Dialog && other)      = delete;

private:

    QVBoxLayout* main_layout;
    QHBoxLayout* buttons_layout;
    QGroupBox* buttons_group;
    QTreeView* file_system_view;
    QFileSystemModel* model;
    QPushButton* cancel_button;
    QPushButton* ok_button;



    void create_file_system_dialog();
    void create_alert_dialog(const QList<QString> files);
    //void clear();

private slots:

    void on_cancel_button_clicked();
    void on_ok_button_clicked();
    void on_dialog_finished(int);

signals:

    void directory_selected(QString);
    void cancel_button_selected();
    void ok_alert_button_selected();
    void dialog_finished(int);
};

#endif // DIALOG_H
