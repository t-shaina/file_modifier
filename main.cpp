#include "creator.h"
#include <sys/locking.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Creator c(&a);
    return a.exec();
}
