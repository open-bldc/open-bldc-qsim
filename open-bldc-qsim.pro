#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T16:36:51
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = open-bldc-qsim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    signalplot.cpp \
    simrunner.cpp \
    sim.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    signalplot.h \
    simrunner.h \
    sim.h

FORMS    += mainwindow.ui

LIBS_PRIVATE += -framework Foundation
