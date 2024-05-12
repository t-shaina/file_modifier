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



    char c1 = '0';
    char c2 = '1';
    int i1 =  c1 - '0';
    int i2 =  c2 - '0';
    quint16 i = i1 << 4 | i2;
    char a1 =
    std::cout << i << std::endl;
    return a.exec();
}
