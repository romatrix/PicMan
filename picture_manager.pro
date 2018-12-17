TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    shasumfile.cpp \
    shasumfilemanager.cpp \
    systemcmd.cpp

HEADERS += \
    shasumfile.h \
    shasumfilemanager.h \
    systemcmd.h
