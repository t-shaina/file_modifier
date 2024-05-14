#include "creator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Creator c(&a);
    return a.exec();
}
