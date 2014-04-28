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
    src/calibration.cpp

HEADERS  += src/mainwindow.h \
    src/curveperso.h \
    src/server.h \
    src/debug.h \
    src/calibration.h

FORMS    += src/IHM.ui


