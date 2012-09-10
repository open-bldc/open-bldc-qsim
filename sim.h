#ifndef SIM_H
#define SIM_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <qcustomplot.h>

#include "csim/src/dyn_model.h"
#include "csim/src/controller.h"

class Sim : public QObject
{
    Q_OBJECT
public:
    explicit Sim(QObject *parent = 0);
    ~Sim();
    void stopSim();

private:
    double time;
    QTimer sendDataTimer;
    bool shouldQuit;
    QMutex shouldQuitMutex;
    QVector<double> *dataTimes;
    QVector<QVector<double> *> *dataValues;
    struct motor motor;
    struct command_vector cv;
    struct perturbation_vector pv;
    struct parameters params;
    struct setpoint setpoint;

signals:
    void newDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues);
    void finished();

public slots:
    void start();
};

#endif // SIM_H
