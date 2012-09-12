#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

TEMPLATE = app

QT       += core network
QT       -= gui

TARGET   = ewapp
CONFIG   += console
CONFIG   -= app_bundle


DEFINES += START=\\\"start\\\" \
        STOP=\\\"stop\\\" \
        RESTART=\\\"restart\\\" \
        RELOAD=\\\"reload\\\" \
        STATE=\\\"state\\\" \
        DAEMON_NAME=\\\"esapps\\\"


HEADERS += src/daemon.hpp \
    src/localsocketipcserver.hpp \
    src/localsocketipcclient.hpp \
    src/settingsmanager.hpp \
    src/controller.hpp \
    src/clientresponse.hpp

SOURCES += src/main.cpp \
    src/daemon.cpp \
    src/localsocketipcserver.cpp \
    src/localsocketipcclient.cpp \
    src/settingsmanager.cpp \
    src/controller.cpp \
    src/clientresponse.cpp



