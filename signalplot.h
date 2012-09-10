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
    void onNewDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues);
    
};

#endif // SIGNALPLOT_H
