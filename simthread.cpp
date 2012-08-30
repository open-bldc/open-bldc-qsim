#include <QtDebug>
#include "simthread.h"
#include <cmath>

SimThread::SimThread(QObject *parent) :
    QThread(parent)
{
    shouldQuit = false;
    time = 4.0;
}

void SimThread::run()
{
    qDebug() << "Hello from the simulator thread " << thread()->currentThreadId();

    double value;
    for (int i = 0; i<10000; i++)
    {
        time += 1.0/1000.0;
        value = sin((M_PI/500)*i);
        qDebug() << "Adding data point " << value << " at time " << time;
        emit sendDataPoint(time, value);
        //msleep(100);
        double blubb;
        for (int j = 0; j<100000; j++){
            blubb = sin(cos(tan((double)i)));
            blubb = blubb * blubb;
        }
        shouldQuitMutex.lock();
        if (shouldQuit){
            shouldQuitMutex.unlock();
            return;
        }
        shouldQuitMutex.unlock();
    }
}

void SimThread::stopSim()
{
    shouldQuitMutex.lock();
    shouldQuit = true;
    shouldQuitMutex.unlock();
}
