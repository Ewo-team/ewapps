#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------


TEMPLATE = subdirs
SUBDIRS = ewapp-service ewapp



include(libs/qt-solutions/qtsingleapplication/src/qtsinglecoreapplication.pri)
include(libs/qt-solutions/qtservice/src/qtservice.pri)

ewapp.depends = ewapp-service

