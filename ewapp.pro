#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

TEMPLATE = app

QT       += core network
QT       -= gui

TARGET   = ewapp
CONFIG   += console debug
CONFIG   -= app_bundle



DEFINES += START=\\\"start\\\" \
        STOP=\\\"stop\\\" \
        RESTART=\\\"restart\\\" \
        RELOAD=\\\"reload\\\" \
        STATE=\\\"state\\\" \
        \
        DAEMON=0\
        CONTROLLER=1\
        \
        RUNNING_DIR=\\\"/usr/local/ewapp/\\\"\
        \
        LOG_DIR=\\\"/var/log/ewapp/\\\"\
        LOG_FILE=\\\"ewapp.log\\\"



HEADERS += src/daemon.hpp \
    src/localsocketipcserver.hpp \
    src/localsocketipcclient.hpp \
    src/settingsmanager.hpp \
    src/controller.hpp \
    src/clientresponse.hpp \
    src/logger.hpp \
    src/plugin/plugin.hpp \
    src/plugin/wsclient.hpp

SOURCES += src/main.cpp \
    src/daemon.cpp \
    src/localsocketipcserver.cpp \
    src/localsocketipcclient.cpp \
    src/settingsmanager.cpp \
    src/controller.cpp \
    src/clientresponse.cpp \
    src/logger.cpp \
    src/plugin/plugin.cpp \
    src/plugin/wsclient.cpp

CONFIG(release, debug|release) {
    DESTDIR = release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
    DEFINES += LOG_LVL=INFO
}
CONFIG(debug, debug|release) {
    DESTDIR = debug
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
    DEFINES += LOG_LVL=DEBUG
    QMAKE_CXXFLAGS += -Wall
}
