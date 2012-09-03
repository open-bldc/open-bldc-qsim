#include <QtDebug>
#include "simthread.h"
#include <cmath>

SimThread::SimThread(QObject *parent) :
    QThread(parent)
{
    shouldQuit = false;
    time = 4.0;
    sendDataTimer.setInterval(40);
    sendDataTimer.setSingleShot(true);
    dataTimes = NULL;
    dataValues = NULL;
}

void SimThread::run()
{
    qDebug() << "Hello from the simulator thread " << thread()->currentThreadId();

    sendDataTimer.start();

    double value;
    for (int i = 0; i<100000; i++)
    {
        time += 1.0/1000.0;
        value = sin((M_PI/500)*i);
        if (dataTimes == NULL) {
            dataTimes = new QVector<double>;
        }
        if (dataValues == NULL) {
            dataValues = new QVector<double>;
        }
        dataTimes->append(time);
        dataValues->append(value);
        if (!sendDataTimer.isActive()) {
            //qDebug() << "Adding " << dataTimes->count() << " data points from " << dataTimes->first() << " to " << dataTimes->last();
            emit sendDataPoints(dataTimes, dataValues);
            dataTimes = NULL;
            dataValues = NULL;
            sendDataTimer.start();
        }
        double blubb;
        for (int j = 0; j<1000; j++){
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

    qDebug() << "Finished generating and sending data.";
}

void SimThread::stopSim()
{
    shouldQuitMutex.lock();
    shouldQuit = true;
    shouldQuitMutex.unlock();
}
