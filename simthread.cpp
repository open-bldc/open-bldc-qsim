#include <QtDebug>
#include "simthread.h"

SimThread::SimThread(QObject *parent) :
    QThread(parent)
{
}

void SimThread::run()
{
    qDebug() << "Hello from the simulator thread " << thread()->currentThreadId();
}
