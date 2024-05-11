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
    QString adding_slash(QString* dir)                          const;
    Modificator::Action str_to_action(QString* act)             const;

public slots:

    void processing(const Current_settings*);
    void working();
    void files_open(const QList<QString>);

signals:

    void has_problem_with_files(const QList<QString>);
};

#endif // MANAGER_H

/*int size = number_of_bytes * 8;
QVector<bool> rez;
rez.resize(size);
int vector_counter = 0;
for (int i = 0; i < hex.size(); i++){
    int ascii = hex.at(i).toLatin1();
    int digit;
    // [0;9]
    if (ascii >= 48 && ascii <= 57) {
        digit = hex.at(i).digitValue();

    }
    // [A; F]
    else if (ascii >= 65 && ascii <= 70) {
        digit = ascii - ascii_diff_between_uppercase_letters;
    }
    // [a;f]
    else if (ascii >= 97 && ascii <= 102) {
        digit = ascii - ascii_diff_between_lowercase_letters;
    }
    //else  обработка случая
    int dec = 0b0000;
    for (int j = 0 ; j < digit; j++){
        dec = dec + 0b0001;
    }
    //rez.at(vector_counter) = dec >> 4;
    vector_counter++;
}*/
