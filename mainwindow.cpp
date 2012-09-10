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
}

MainWindow::~MainWindow()
{
    delete ui;
}
