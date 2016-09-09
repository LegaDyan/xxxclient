#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T11:20:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = T3Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filetransclient.cpp

HEADERS  += mainwindow.h \
    filetransclient.h

FORMS    += mainwindow.ui
