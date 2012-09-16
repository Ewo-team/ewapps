#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

TEMPLATE = app

QT       += core network script
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



HEADERS += src/daemon/daemon.hpp \
    src/daemon/commandargumenthandler.hpp \
    src/localSocket/localsocketipcserver.hpp \
    src/localSocket/localsocketipcclient.hpp \
    src/localSocket/clientresponse.hpp \
    src/utils/settingsmanager.hpp \
    src/utils/logger.hpp \
    src/controller.hpp \
    src/plugin/plugin.hpp \
    src/plugin/wsclient.hpp \
    src/daemon/pluginmanager.hpp

SOURCES += src/main.cpp \
    src/daemon/daemon.cpp \
    src/daemon/commandargumenthandler.cpp \
    src/localSocket/localsocketipcserver.cpp \
    src/localSocket/localsocketipcclient.cpp \
    src/localSocket/clientresponse.cpp \
    src/utils/settingsmanager.cpp \
    src/utils/logger.cpp \
    src/controller.cpp \
    src/plugin/plugin.cpp \
    src/plugin/wsclient.cpp \
    src/daemon/pluginmanager.cpp

CONFIG(release, debug|release) {
    DESTDIR = release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
    DEFINES += LOG_LVL=INFO
    LIBS += -Bdynamic -lwebsocketpp
}
CONFIG(debug, debug|release) {
    DESTDIR = debug
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
    DEFINES += LOG_LVL=DEBUG
    LIBS += -lwebsocketpp-d
    QMAKE_CXXFLAGS += -Bdynamic -Wall
}
