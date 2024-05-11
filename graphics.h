#ifndef GRAGHICS_H
#define GRAGHICS_H

#include "directory_group.h"
#include "dialog.h"
#include "qcheckbox.h"
#include "qcombobox.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class Graphics : public QWidget{
    Q_OBJECT

public:

    Graphics(QWidget* parent = nullptr, int width = 500, int height = 350);
    ~Graphics();
    Graphics(Graphics const& other)            = delete;
    Graphics& operator=(Graphics const& other) = delete;
    Graphics(Graphics && other)                = delete;
    Graphics& operator=(Graphics && other)     = delete;
    QString get_in_dir()     const;
    QString get_mask()       const;
    QString get_out_dir()    const;
    bool get_rm_state()      const;
    bool get_rewrite_state() const;
    int get_interval_sec()   const;
    QString get_var()        const;

private:

    Directory_group* in_dir_group;
    QLineEdit* mask_edit;
    Directory_group* out_dir_group;
    QCheckBox* rm_check_box;
    QComboBox* action_combo_box;
    QComboBox* timer_combo_box;
    QLineEdit* var_edit;
    QPushButton* accept_button;
    QGridLayout* layout;

    void setting_combo_boxes(bool is_default_setting = true);
    void setting_edits(bool is_default_setting = true);
    void setting_button(bool is_default_setting = true);
    void settingg_check_box(bool is_default_setting = true);

private slots:

   void on_accept_button_clicked();

signals:

    void settings_ready();
};

#endif // GRAGHICS_H
