#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QFile>
#include <QDir>

class Modificator : public QObject{
    Q_OBJECT
    Q_ENUMS(Actions)

public:

    Modificator(QList<QString> in_files,
                QString in,
                QString out,
                bool rm_state,
                bool rewrite_state,
                QVector<bool>* var);
    ~Modificator();
    Modificator(Modificator const & other)            = delete;
    Modificator& operator=(Modificator const & other) = delete;
    Modificator(Modificator && other)                 = delete;
    Modificator& operator=(Modificator && other)      = delete;
    int modification();

    enum Action {
        Rewrite = 0,
        Modification
    };

private:

    QList<QString>* in_files_;
    const QDir* in_dir_;
    const QDir* out_dir_;
    bool rm_state_;
    bool rewrite_state_;
    const QVector<bool>* var_;


    QSharedPointer<QByteArray> bool_operation(QFile* file) const;
    QSharedPointer<QByteArray> do_xor(QFile* file) const;
    bool rm_file(QFile* file) const;
    bool write_to_file(const QFile* in_file, const QDir* out_dir, const QSharedPointer<QByteArray> data) const;
    QString modification_out_file_name(const QFile* file) const;
    bool is_file_name_exist(const QFile* file, const QDir* dir) const;

signals:

    void these_files_open(const QList<QString>);

};

#endif // MODIFICATOR_H
