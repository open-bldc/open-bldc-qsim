#ifndef SIMRUNNER_H
#define SIMRUNNER_H

#include <QObject>
#include <QThread>
#include "sim.h"

class SimRunner : public QObject
{
    Q_OBJECT
public:
    explicit SimRunner(QObject *parent = 0);
    
private:
    QThread *thread;
    Sim *sim;
    bool running;

signals:
    void newDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues);
    
public slots:
    void runSim(void);
    void onNewDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues);
    void simFinished(void);
    
};

#endif // SIMRUNNER_H
