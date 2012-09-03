#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&st, SIGNAL(sendDataPoints(QVector<double> *, QVector<double> *)), ui->signalPlot, SLOT(addDataPoints(QVector<double> *, QVector<double> *)), Qt::QueuedConnection);
    st.start();
    qDebug() << "Hello from GUI thread.";


    ui->signalPlot->replot();
}

MainWindow::~MainWindow()
{
    st.stopSim();
    st.wait();
    delete ui;
}
