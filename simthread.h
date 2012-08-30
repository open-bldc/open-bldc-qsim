#ifndef SIMTHREAD_H
#define SIMTHREAD_H

#include <QThread>
#include <QMutex>

class SimThread : public QThread
{
    Q_OBJECT
public:
    explicit SimThread(QObject *parent = 0);
    void stopSim();

private:
    double time;
    bool shouldQuit;
    QMutex shouldQuitMutex;
    void run();
signals:
    void sendDataPoint(double time, double val);
    
public slots:
    
};

#endif // SIMTHREAD_H
