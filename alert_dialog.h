#ifndef ALERT_DIALOG_H
#define ALERT_DIALOG_H

#include <QObject>
#include <QDialog>
#include <Qlabel>
#include <QPushButton>
#include <QVBoxLayout>

class Alert_dialog : public QDialog{

    Q_OBJECT

public:

    Alert_dialog();
    Alert_dialog(QWidget* parent = nullptr, const QList<QString> = {});
    ~Alert_dialog();
    Alert_dialog(Alert_dialog const& other)             = delete;
    Alert_dialog& operator=(Alert_dialog const& other)  = delete;
    Alert_dialog(Alert_dialog && other)                 = delete;
    Alert_dialog& operator=(Alert_dialog && other)      = delete;

private:

    QVBoxLayout* main_layout;
    QLabel* alert_label;
    QPushButton* ok_alert_button;

private slots:

    void on_ok_alert_button_clicked();
    void dialog_finished(int code);

signals:

    void ok_alert_button_selected();
    void alert_dialog_finished(int);
};

#endif // ALERT_DIALOG_H
