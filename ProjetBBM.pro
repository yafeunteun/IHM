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
    src/calibration.cpp \
    src/imu.cpp \
    dataholder.cpp \
    dataholderproxy.cpp \
    dataset.cpp

HEADERS  += src/mainwindow.h \
    src/curveperso.h \
    src/server.h \
    src/debug.h \
    src/calibration.h \
    src/imu.h \
    dataholder.h \
    dataholderproxy.h \
    dataset.h

FORMS    += src/IHM.ui


