#include <QtGui/QApplication>
#include "mainwindow.h"
#include "simthread.h"

int main(int argc, char *argv[])
{
    int ret;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
