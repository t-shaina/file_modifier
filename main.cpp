#include "mainwindow.h"
#include "creator.h"
#include <QApplication>
#include <iostream>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creator c(&a);


    QChar symbol = 'D';
    int ascii_dec = symbol.unicode();
    int counter = 0;
    quint8 rez = 0;
    if (ascii_dec >= 48 && ascii_dec < 48 + 10){
        counter += ascii_dec - 48;
    }
    if (ascii_dec >= 65 && ascii_dec < 65 + 6){
        counter += ascii_dec - 65 + 10;
    }
    for (int i = 0; i < counter; i++){
        rez = rez + 1;
    }

    std::cout << (int)rez << std::endl;
    //int rez  = c ^ i;
    //std::cout << rez << std::endl;
    return a.exec();
}
