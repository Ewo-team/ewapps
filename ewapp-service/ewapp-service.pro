#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = ewapp-service
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/daemon.cpp

HEADERS += \
    src/daemon.hpp

include(../libs/qt-solutions/qtservice/src/qtservice.pri)
