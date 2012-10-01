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
    void setPWMDuty(double duty);
    double getPWMDuty(void);

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
    QMutex setpointMutex;

signals:
    void newDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues);
    void finished();

public slots:
    void start();
};

#endif // SIM_H
