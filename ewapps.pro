#-------------------------------------------------
#
# Project created by QtCreator 2012-08-18T07:43:54
#
#-------------------------------------------------

VERSION=0.0.6

TEMPLATE = app

QT       += core network script
QT       -= gui

TARGET   = ewapp
CONFIG   += console debug
CONFIG   -= app_bundle



DEFINES += ACTION_START=\\\"start\\\" \
        ACTION_STOP=\\\"stop\\\" \
        ACTION_RESTART=\\\"restart\\\" \
        ACTION_RELOAD=\\\"reload\\\" \
        ACTION_STATE=\\\"state\\\" \
        \
        DAEMON=0\
        CONTROLLER=1\
        \
        RUNNING_DIR=\\\"/usr/local/ewapp/\\\"\
        \
        LOG_DIR=\\\"/var/log/ewapp/\\\"\
        LOG_FILE=\\\"ewapp.log\\\"


LIBS += -lpthread  -lsegvcatch -Bdynamic -lwebsocketpp -lboost_system -lboost_date_time -lboost_regex -lboost_random -lboost_program_options -lboost_thread

HEADERS += src/daemon/daemon.hpp \
    src/controller.hpp \
    src/daemon/commandargumenthandler.hpp \
    src/wsSocket/websocketserver.hpp \
    src/localSocket/localsocketipcserver.hpp \
    src/utils/daemonize.hpp \
    src/common/localSocket/localsocketipcclient.hpp \
    src/common/localSocket/clientresponse.hpp \
    src/common/utils/settingsmanager.hpp \
    src/common/utils/logger.hpp \
    src/common/plugin/plugin.hpp \
    src/common/wsSocket/websocketconnection.hpp

SOURCES += src/main.cpp \
    src/controller.cpp \
    src/daemon/daemon.cpp \
    src/daemon/commandargumenthandler.cpp \
    src/wsSocket/websocketserver.cpp \
    src/localSocket/localsocketipcserver.cpp \
    src/utils/daemonize.cpp \
    src/common/localSocket/localsocketipcclient.cpp \
    src/common/localSocket/clientresponse.cpp \
    src/common/utils/settingsmanager.cpp \
    src/common/utils/logger.cpp \
    src/common/plugin/plugin.cpp \
    src/common/wsSocket/websocketconnection.cpp

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
    QMAKE_CXXFLAGS += -Bdynamic -Wall
}
