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

#include <QtDebug>
#include "sim.h"
#include <cmath>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include "csim/src/misc_utils.h"

Sim::Sim(QObject *parent) :
    QObject(parent)
{
    shouldQuit = false;
    time = 0.0;
    sendDataTimer.setInterval(100);
    sendDataTimer.setSingleShot(true);
    dataTimes = NULL;
    dataValues = NULL;

    /* initializing simulator structs */
    motor.inertia = 1.1;
    motor.damping = 0.5;
    motor.static_friction = 0.1;
    motor.Kv = 1./32.3*1000;
    motor.L = 0.0207;
    motor.M = -0.00069;
    motor.R = 11.9;
    motor.VDC = 100;
    motor.NbPoles = 4;

    cv.hu = NULL;
    cv.lu = NULL;
    cv.hv = NULL;
    cv.lv = NULL;
    cv.hw = NULL;
    cv.lw = NULL;

    pv.torque = 0.02;

    params.m = &motor;
    params.cv = &cv;
    params.pv = &pv;

    setpointMutex.lock();
    setpoint.pwm_frequency = 16000;
    setpoint.pwm_duty = 0.75;
    setpointMutex.unlock();
}

Sim::~Sim()
{
    qDebug() << "Deleting simulator...";
}

void Sim::start()
{
    qDebug() << "Hello from the simulator thread " << thread()->currentThreadId();

    sendDataTimer.start();

    gsl_odeiv2_system sys = {dyn, NULL, 5, &params};

    // prams: system, driver, initial step size, absolute error, relative error
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);

    int count = 0;
    double t = 0.0;
    double sim_freq = 100000.0;
    double t_step = 1.0 / sim_freq;
    struct state_vector sv;
    bool running = true;
    int status;

    init_state(&sv);
    setpointMutex.lock();
    run(t, t + t_step, &setpoint, &motor, &sv, &cv);
    setpointMutex.unlock();

    double ti = t;
    while(running) {
        ti += t_step;
        status = gsl_odeiv2_driver_apply(d, &t, ti, (double *)&sv);

        if (status != GSL_SUCCESS) {
            qDebug() << "error, return value=" << status;
        }

        if (dataTimes == NULL) {
            dataTimes = new QVector<double>;
        }
        if (dataValues == NULL) {
            dataValues = new QVector<QVector<double> *>;
            dataValues->append(new QVector<double>);
            dataValues->append(new QVector<double>);
            dataValues->append(new QVector<double>);
            dataValues->append(new QVector<double>);
            dataValues->append(new QVector<double>);
        }

        if (count == 0) {
            count = 0;
        dataTimes->append(t);
        (*dataValues)[0]->append(sv.iu);
        (*dataValues)[1]->append(sv.iv);
        (*dataValues)[2]->append(sv.iw);
        (*dataValues)[3]->append(norm_angle(sv.theta)/100); /* position */
        (*dataValues)[4]->append(sv.omega/50);             /* speed */
        } else {
            ++count;
        }

        if (!sendDataTimer.isActive()) {
            //qDebug() << "Adding " << dataTimes->count() << " data points from " << dataTimes->first() << " to " << dataTimes->last();
            emit newDataPoints(dataTimes, dataValues);
            dataTimes = NULL;
            dataValues = NULL;
            sendDataTimer.start();
        }

        setpointMutex.lock();
        run(t, t + t_step, &setpoint, &motor, &sv, &cv);
        setpointMutex.unlock();

        shouldQuitMutex.lock();
        if (shouldQuit) {
            running = false;
        }
        shouldQuitMutex.unlock();
    }

    gsl_odeiv2_driver_free (d);

    sendDataTimer.stop();

    qDebug() << "Finished generating and sending data.";
    emit finished();
}

void Sim::stopSim()
{
    shouldQuitMutex.lock();
    shouldQuit = true;
    shouldQuitMutex.unlock();
}

void Sim::setPWMDuty(double duty)
{
    setpointMutex.lock();
    setpoint.pwm_duty = duty;
    setpointMutex.unlock();
}
