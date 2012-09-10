#include "simrunner.h"

#include <QDebug>

SimRunner::SimRunner(QObject *parent) :
    QObject(parent)
{
    running = false;
    thread = NULL;
}

void SimRunner::runSim(void)
{

    if ((thread == NULL) || (thread->isFinished())) {
        running = true;
        qDebug() << "Activating simulation.";

        if (thread == NULL) {
            thread = new QThread();
        }
        sim = new Sim();
        sim->moveToThread(thread);
        connect(thread, SIGNAL(started()), sim, SLOT(start()), Qt::QueuedConnection);
        connect(sim, SIGNAL(newDataPoints(QVector<double>*,QVector<double>*)), this, SLOT(onNewDataPoints(QVector<double>*,QVector<double>*)), Qt::QueuedConnection);
        connect(sim, SIGNAL(finished()), thread, SLOT(quit()), Qt::QueuedConnection);
        connect(sim, SIGNAL(finished()), sim, SLOT(deleteLater()), Qt::QueuedConnection);
        connect(sim, SIGNAL(finished()), this, SLOT(simFinished()));

        thread->start();
    } else {
        qDebug() << "Thread still running ...";
    }
}

void SimRunner::onNewDataPoints(QVector<double> *dataTimes, QVector<double> *dataValues)
{
    emit newDataPoints(dataTimes, dataValues);
}

void SimRunner::simFinished()
{
    qDebug() << "Simulator finished signal...";
}
