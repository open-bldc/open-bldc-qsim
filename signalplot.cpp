#include "signalplot.h"

SignalPlot::SignalPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    setupPlot();
}

void SignalPlot::setupPlot()
{
    addGraph(); // blue line
    graph(0)->setPen(QPen(Qt::blue));
    //graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    //graph(0)->setAntialiasedFill(true);

    xAxis->setTickLabelType(QCPAxis::ltNumber);
    xAxis->setNumberFormat("f");
    xAxis->setNumberPrecision(3);
    xAxis->setAutoTickStep(false);
    xAxis->setTickStep(1);
    setupFullAxesBox();

    xAxis->setLabel("Time (s)");

    {
        double value;
        for (int i = 0; i<4000; i++) {
            value = sin((M_PI/500)*i);
            graph(0)->addData((double)(1.0/1000.0)*i, value);
        }
    }

    graph(0)->rescaleAxes(false, false);
}

void SignalPlot::addDataPoint(double time, double val)
{
    qDebug() << "Getting point " << val;
    graph(0)->addData(time, val);
    graph(0)->removeDataBefore(time - 4);
    xAxis->setRange(time,4,Qt::AlignRight);
    replot();
}
