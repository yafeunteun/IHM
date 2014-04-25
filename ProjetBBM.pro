#-------------------------------------------------
#
# Project created by QtCreator 2013-02-17T16:12:31
#
#-------------------------------------------------

QT       += core gui\
            network\
            gui declarative
            designer

QMAKE_CXXFLAGS += -std=c++11

TARGET = ProjetBBM
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    curveperso.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    curveperso.h \
    server.h \
    debug.h


CONFIG += qwt
CONFIG += console debug

FORMS    += IHM.ui

OTHER_FILES += \
    Img/stop.png \
    Img/play.png \
    Img/pause.png


