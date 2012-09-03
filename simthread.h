#ifndef SIMTHREAD_H
#define SIMTHREAD_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <qcustomplot.h>

class SimThread : public QThread
{
    Q_OBJECT
public:
    explicit SimThread(QObject *parent = 0);
    void stopSim();

private:
    double time;
    QTimer sendDataTimer;
    bool shouldQuit;
    QMutex shouldQuitMutex;
    QVector<double> *dataTimes;
    QVector<double> *dataValues;
    void run();

signals:
    void sendDataPoints(QVector<double> *dataTimes, QVector<double> *dataValues);

public slots:
    
};

#endif // SIMTHREAD_H
