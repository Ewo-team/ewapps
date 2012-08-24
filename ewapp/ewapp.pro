#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = ewapp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = subdirs
SUBDIRS = ewapp-service ewapp

SOURCES += src/main.cpp \
    src/controller.cpp

HEADERS += \
    src/controller.hpp


include(../libs/qt-solutions/qtsingleapplication/src/qtsinglecoreapplication.pri)
include(../libs/qt-solutions/qtservice/src/qtservice.pri)
