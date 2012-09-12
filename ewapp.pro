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


#HEADERS += src/daemon.hpp \
#    src/localsocketipcserver.hpp \
#    src/localsocketipcclient.hpp \
#    src/settingsmanager.hpp \
#    src/controller.hpp \
#    src/clientresponse.hpp

#SOURCES += src/main.cpp \
#    src/daemon.cpp \
#    src/localsocketipcserver.cpp \
#    src/localsocketipcclient.cpp \
#    src/settingsmanager.cpp \
#    src/controller.cpp \
#    src/clientresponse.cpp

HEADERS += src/settingsmanager.hpp
SOURCES += src/main.cpp \
            src/settingsmanager.cpp


release:DESTDIR = release
release:OBJECTS_DIR = release/.obj
release:MOC_DIR = release/.moc
release:RCC_DIR = release/.rcc
release:UI_DIR = release/.ui

debug:DESTDIR = debug
debug:OBJECTS_DIR = debug/.obj
debug:MOC_DIR = debug/.moc
debug:RCC_DIR = debug/.rcc
debug:UI_DIR = debug/.ui
