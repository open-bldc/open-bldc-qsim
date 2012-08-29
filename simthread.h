#ifndef SIMTHREAD_H
#define SIMTHREAD_H

#include <QThread>

class SimThread : public QThread
{
    Q_OBJECT
public:
    explicit SimThread(QObject *parent = 0);

private:
    void run();
signals:
    void sendDataPoint();
    
public slots:
    
};

#endif // SIMTHREAD_H
