#include <QtGui/QApplication>
#include "mainwindow.h"
#include "simthread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SimThread st;
    st.start();
    qDebug() << "Hello from GUI thread " << a.thread()->currentThreadId();
    st.wait();

    return a.exec();
}
