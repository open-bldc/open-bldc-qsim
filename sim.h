#ifndef SIM_H
#define SIM_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <qcustomplot.h>

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

signals:
    void newDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues);
    void finished();

public slots:
    void start();
};

#endif // SIM_H
