#ifndef MANAGER_H
#define MANAGER_H

#include "current_settings.h"
#include "modificator.h"

#include <QObject>
#include <QTimer>

class Manager : public QObject{

    Q_OBJECT

public:

    Manager(QObject *parent = nullptr);
    ~Manager();
    Manager(Manager const & other)            = delete;
    Manager& operator=(Manager const & other) = delete;
    Manager(Manager && other)                 = delete;
    Manager& operator=(Manager && other)      = delete;

private:

    QTimer* timer;
    Modificator* modificator;

    QVector<QString> apply_mask(QString* in_dir, QString* mask) const;

public slots:

    void processing(const Current_settings*);
    void working();
    void files_open();

signals:

    void has_problem_with_files();
};

#endif // MANAGER_H

