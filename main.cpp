#include "mainwindow.h"
#include "creator.h"
#include <QApplication>
#include <fstream>
#include <QFile>
#include <QDir>
#include <QDataStream>

quint8 char_to_int(QChar symbol) {
    symbol.toUpper();
    int ascii_dec = symbol.unicode();
    int counter   = 0;
    quint8 rez    = 0;
    if (ascii_dec >= 48 && ascii_dec < 48 + 10){
        counter += ascii_dec - 48;
    }
    if (ascii_dec >= 65 && ascii_dec < 65 + 6){
        counter += ascii_dec - 65 + 10;
    }
    for (int i = 0; i < counter; i++){
        rez = rez + 1;
    }
    return rez;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Creator c(&a);

    //MainWindow w;
    return a.exec();
}
