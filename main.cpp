#include "mainwindow.h"
#include "creator.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Creator c(&a);
    /*QDir::setCurrent("C:/Qt");
    QFile file("bin");
    file.open(QIODeviceBase::ReadOnly);
    int bytes = file.bytesAvailable();
    QByteArray arr = file.readAll();
    qDebug() << bytes << arr;*/
    return a.exec();
}
