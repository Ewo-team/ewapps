#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = ewo-app
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/daemon.cpp

include(libs/qt-solutions/qtsingleapplication/src/qtsinglecoreapplication.pri)

HEADERS += \
    src/daemon.hpp
