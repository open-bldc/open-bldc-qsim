/*
 * Open-BLDC QSim - Open BrushLess DC Motor Controller QT Simulator GUI
 * Copyright (C) 2012 by Piotr Esden-Tempski <piotr@esden.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    addGraph(); // red line
    graph(1)->setPen(QPen(Qt::red));
    addGraph(); // green line
    graph(2)->setPen(QPen(Qt::green));
    //graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    //graph(0)->setAntialiasedFill(true);

    xAxis->setTickLabelType(QCPAxis::ltNumber);
    xAxis->setNumberFormat("f");
    xAxis->setNumberPrecision(3);
    xAxis->setAutoTickStep(false);
    xAxis->setTickStep(0.005);
    setupFullAxesBox();

    xAxis->setLabel("Time (s)");

#if 0
    {
        double value;
        for (int i = 0; i<4000; i++) {
            value = sin((M_PI/500)*i);
            graph(0)->addData((double)(1.0/1000.0)*i, value);
            graph(1)->addData((double)(1.0/1000.0)*i, value/5);
            graph(2)->addData((double)(1.0/1000.0)*i, value/10);
        }
    }
#endif
    graph(0)->rescaleAxes(false, false);
    //graph(1)->rescaleAxes(false, false);
    //graph(2)->rescaleAxes(false, false);
}

void SignalPlot::onNewDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues)
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

    graph(0)->addData(*dataTimes, *(*dataValues)[0]);
    graph(0)->removeDataBefore(dataTimes->last() - 0.01);
    graph(1)->addData(*dataTimes, *(*dataValues)[1]);
    graph(1)->removeDataBefore(dataTimes->last() - 0.01);
    graph(2)->addData(*dataTimes, *(*dataValues)[2]);
    graph(2)->removeDataBefore(dataTimes->last() - 0.01);
    xAxis->setRange(dataTimes->last(), 0.01, Qt::AlignRight);
    yAxis->setRange(-.000001, .000001);
    qDebug() << "iu " << (*dataValues)[0]->last() << " iv " << (*dataValues)[1]->last() << " iw " << (*dataValues)[2]->last();
    replot();

    delete dataTimes;
    delete dataValues;
}
