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

void SignalPlot::onNewDataPoints(QVector<double> *dataTimes, QVector<double> *dataValues)
{
#if 0
    QVectorIterator<double> tn(*dataTimes);
    QVectorIterator<double> vn(*dataValues);
    int count = 0;

    while (tn.hasNext()) {
        qDebug() << "Getting point " << count << " with time " << tn.next() << " and value " << vn.next();
        count++;
    }
#endif

    graph(0)->addData(*dataTimes,*dataValues);
    graph(0)->removeDataBefore(dataTimes->last() - 4);
    xAxis->setRange(dataTimes->last(), 4, Qt::AlignRight);
    replot();
    delete dataTimes;
    delete dataValues;
}
