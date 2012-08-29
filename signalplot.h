#ifndef SIGNALPLOT_H
#define SIGNALPLOT_H

#include "qcustomplot.h"

class SignalPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit SignalPlot(QWidget *parent = 0);

private:
    void setupPlot();

signals:
    
public slots:
    
};

#endif // SIGNALPLOT_H
