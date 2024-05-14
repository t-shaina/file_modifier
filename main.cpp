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
    return a.exec();
}
