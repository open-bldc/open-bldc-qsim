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

#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sr = new SimRunner();

    connect(ui->runSimButton, SIGNAL(clicked()), sr, SLOT(runSim()));
    connect(sr, SIGNAL(newDataPoints(QVector<double>*,QVector<QVector<double> *>*)), ui->signalPlot, SLOT(onNewDataPoints(QVector<double>*,QVector<QVector<double> *>*)));

    ui->PWMDutySpinBox->setValue(sr->getPWMDuty()*100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PWMDutySlider_valueChanged(int value)
{
    ui->PWMDutySpinBox->setValue(value/10.0);
}

void MainWindow::on_PWMDutySpinBox_valueChanged(double arg1)
{
    ui->PWMDutySlider->setValue(arg1 * 10);
    if (ui->PWMDutySendLockButton->isChecked()) {
        sr->setPWMDuty(arg1/100.0);
    }
}

void MainWindow::on_PWMDutySendButton_clicked()
{
    sr->setPWMDuty(ui->PWMDutySpinBox->value()/100.0);
}

void MainWindow::on_PWMDutySendLockButton_toggled(bool checked)
{
    if (checked) {
        ui->PWMDutySendButton->setChecked(true);
        ui->PWMDutySendButton->setEnabled(false);
    } else {
        ui->PWMDutySendButton->setChecked(false);
        ui->PWMDutySendButton->setEnabled(true);
    }
}
