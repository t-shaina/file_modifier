#include "mainwindow.h"
#include "creator.h"
#include <QApplication>
#include <iostream>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Creator c(&a);



    QString str = "FFFFFFFF";
    QByteArray x = str.toLocal8Bit();
    QByteArray rez;
    QFile file("test6.txt");
    QDir::setCurrent("C:\\Qt");
    file.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text);
    QByteArray arr = file.read(8);
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr.at(i);
    std::cout << std::endl;
    for (int i = 0; i < arr.size(); i++)
        std::cout << x.at(i);
    std::cout << std::endl;
    return a.exec();
}
