######################################################################
# Automatically generated by qmake (2.01a) sam. 18. ao�t 21:50:03 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src examples\console examples\loader examples\trivial
INCLUDEPATH += .

# Input
HEADERS += src/qtlocalpeer.h \
           src/qtlockedfile.h \
           src/qtsingleapplication.h \
           src/qtsinglecoreapplication.h \
           src/qtlockedfile.cpp \
           src/qtlockedfile_win.cpp \
           src/qtlockedfile_unix.cpp
SOURCES += src/qtlocalpeer.cpp \
           src/qtlockedfile.cpp \
           src/qtlockedfile_unix.cpp \
           src/qtlockedfile_win.cpp \
           src/qtsingleapplication.cpp \
           src/qtsinglecoreapplication.cpp \
           examples/console/main.cpp \
           examples/loader/main.cpp \
           examples/trivial/main.cpp