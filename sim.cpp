#include <QtDebug>
#include "sim.h"
#include <cmath>

Sim::Sim(QObject *parent) :
    QObject(parent)
{
    shouldQuit = false;
    time = 4.0;
    sendDataTimer.setInterval(40);
    sendDataTimer.setSingleShot(true);
    dataTimes = NULL;
    dataValues = NULL;
}

Sim::~Sim()
{
    qDebug() << "Deleting simulator...";
}

void Sim::start()
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
            emit newDataPoints(dataTimes, dataValues);
            dataTimes = NULL;
            dataValues = NULL;
            sendDataTimer.start();
        }
        double blubb;
        for (int j = 0; j<100; j++){
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
    sendDataTimer.stop();

    qDebug() << "Finished generating and sending data.";
    emit finished();
}

void Sim::stopSim()
{
    shouldQuitMutex.lock();
    shouldQuit = true;
    shouldQuitMutex.unlock();
}
