#include "testtask.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testtask w;
    w.show();
    return a.exec();
}
