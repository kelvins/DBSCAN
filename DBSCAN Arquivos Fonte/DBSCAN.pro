#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T09:20:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DBSCAN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    dbscan.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    dbscan.h

FORMS    += mainwindow.ui
