#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QFile>
#include <QDir>

class Manager;

class Modificator : public QObject{

    Q_OBJECT

public:

    Modificator(QList<QString> in_files,
                QString in,
                QString out,
                bool rm_state,
                bool rewrite_state,
                QString var);
    ~Modificator();
    Modificator(Modificator const & other)            = delete;
    Modificator& operator=(Modificator const & other) = delete;
    Modificator(Modificator && other)                 = delete;
    Modificator& operator=(Modificator && other)      = delete;
    void modification();

private:

    QList<QString>* in_files_;
    const QString* in_dir_;
    const QString* out_dir_;
    bool rm_state_;
    bool rewrite_state_;
    const QString* var_;

    QSharedPointer<QByteArray> file_modification(QFile* file)                            const;
    QSharedPointer<QByteArray> read_from_file(QFile* file)                               const;
    void do_operation(QSharedPointer<QByteArray> in_data)                                const;
    char do_xor(char inp, QChar var_first, QChar var_second)                             const;
    QString modification_out_file_name(const QString file_name)                          const;
    QString choosing_valid_file_name_in_dir(const QString file_name, const QString* dir) const;
    bool is_file_name_exist(const QString file_name, const QString* dir) const;
    quint8 char_to_int(QChar symbol)                          const;
    bool is_open(const QFile* file, const QString* dir) const;
    void rm_file(QFile* file)                                 const;
    bool write_to_file(const QFile* in_file, const QString* out_dir, const QSharedPointer<QByteArray> data) const;

signals:

    void some_files_open();
};

#endif // MODIFICATOR_H
