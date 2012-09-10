#ifndef SIGNALPLOT_H
#define SIGNALPLOT_H

#include "qcustomplot.h"

class SignalPlot : public QCustomPlot
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle)
public:
    explicit SignalPlot(QWidget *parent = 0);

private:
    void setupPlot();

signals:

public slots:
    void onNewDataPoints(QVector<double> *dataTimes, QVector<double> *dataValues);
    
};

#endif // SIGNALPLOT_H
