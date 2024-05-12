#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QFile>
#include <QDir>

class Modificator : public QObject{
    Q_OBJECT

public:

    Modificator(QList<QString> in_files,
                QString in,
                QString out,
                bool rm_state,
                bool rewrite_state,
                QByteArray var);
    ~Modificator();
    Modificator(Modificator const & other)            = delete;
    Modificator& operator=(Modificator const & other) = delete;
    Modificator(Modificator && other)                 = delete;
    Modificator& operator=(Modificator && other)      = delete;
    int modification();

private:

    QList<QString>* in_files_;
    const QDir* in_dir_;
    const QDir* out_dir_;
    bool rm_state_;
    bool rewrite_state_;
    const QByteArray* var_;

    QSharedPointer<QByteArray> modification(QFile* file)        const;
    QSharedPointer<QByteArray> read_from_file(QFile* file)      const;
    bool do_operation(QSharedPointer<QByteArray> in_data)       const;
    bool rm_file(QFile* file)                                   const;
    char do_xor(char inp, QChar var_first, QChar var_second)    const;
    QString modification_out_file_name(const QFile* file)       const;
    bool is_file_name_exist(const QFile* file, const QDir* dir) const;
    bool write_to_file(const QFile* in_file, const QDir* out_dir, const QSharedPointer<QByteArray> data) const;
    quint8 char_to_int(QChar symbol) const;

signals:

    void these_files_open(const QList<QString>);

};

#endif // MODIFICATOR_H
