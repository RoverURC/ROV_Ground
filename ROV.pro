#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T15:59:07
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rov.cpp \
    joypadcontroller.cpp

HEADERS  += mainwindow.h \
    rov.h \
    joypadcontroller.h

FORMS    += mainwindow.ui


LIBS += -lSDL
