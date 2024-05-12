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
    //Creator c(&a);
    QDir::setCurrent("C:/Qt");
    //QFile file("test6.txt");
    QFile file2("bin");
   // file.open(QIODeviceBase::ReadOnly);
    file2.open(QIODeviceBase::ReadOnly);
    //QByteArray str = file.readAll();
    QByteArray b = file2.readAll();
    quint8 x = 255;
    for (int i = 0; i < b.size(); i++){
        quint8 y = b.at(i)  ^ x;
        qDebug() << b.at(i) << (int)y;
    }
    /*for (int i = 0; i < str.size(); i++){
        quint8 h1 = char_to_int( str.at(i));
        quint8 h2 = char_to_int( str.at(++i));
        quint8 h = h1 << 4 | h2;
        quint8 y = h  ^ x;
        qDebug() << h << (int)y;
    }
    QDataStream in_str(&file);
    QByteArray in_stream;

    qint32 bytes = in_str.readRawData(in_stream.data(), 8);
    for (int i = 0; i < in_stream.size(); i++){
        quint8 y = in_stream.at(i)  ^ x;
        qDebug() << in_stream.at(i) << (int)y;
    }*/

    file2.close();
    //MainWindow* w = new MainWindow(&a);
    return a.exec();
}
