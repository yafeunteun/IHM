QT       += core gui\
            network

QMAKE_CXXFLAGS += -std=c++11

TARGET = ProjetBBM
TEMPLATE = app

CONFIG += qwt
CONFIG += console debug

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/curveperso.cpp \
    src/server.cpp \
    calibration.cpp

HEADERS  += src/mainwindow.h \
    src/curveperso.h \
    src/server.h \
    src/debug.h \
    calibration.h

FORMS    += src/IHM.ui


