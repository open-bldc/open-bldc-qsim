#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupCustomPlot(ui->customPlot);

    ui->customPlot->replot();
}

void MainWindow::setupCustomPlot(QCustomPlot *customPlot)
{

    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    //customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    //customPlot->graph(0)->setAntialiasedFill(true);

    customPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
    customPlot->xAxis->setNumberFormat("f");
    customPlot->xAxis->setNumberPrecision(3);
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(1);
    customPlot->setupFullAxesBox();

    customPlot->xAxis->setLabel("Time (s)");

    {
        double value;
        for (int i = 0; i<4000; i++) {
            value = sin((M_PI/500)*i);
            customPlot->graph(0)->addData((double)(1.0/1000.0)*i, value);
        }
    }

    customPlot->graph(0)->rescaleAxes(false, false);

}

MainWindow::~MainWindow()
{
    delete ui;
}
