QT       += core gui\
            network \
            widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = ProjetBBM
TEMPLATE = app

CONFIG += qwt
CONFIG += console debug

# Static linking
INCLUDEPATH += C:\QwtSource-static\qwt-6.1.0\src
LIBS += -LC:\QwtSource-static\qwt-6.1.0\lib -lqwt

#QWT Headers
#QWT_LOCATION = C:\QwtSource\qwt-6.1.0
#INCLUDEPATH += $${QWT_LOCATION}/src

#QWT Library
#LIBS = -L$${QWT_LOCATION}/lib -lqwt

# The following section is to select static lib base on debug or release build
#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#mac:LIBS = $$member(LIBS, 0) \
#$$member(LIBS, 1)_debug
#win32:LIBS = $$member(LIBS, 0) \
#$$member(LIBS, 1)d
#}

# QExtSerialPort Library
CONFIG += extserialport
include(3rdparty/qextserialport/src/qextserialport.pri)


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/server.cpp \
    src/imu.cpp \
    src/dataholder.cpp \
    src/dataset.cpp \
    src/graph.cpp \
    src/curve.cpp \
    src/proxystrategy.cpp \
    src/serialport.cpp \
    src/acquisitionsettings.cpp \
    src/datasource.cpp \
    src/filtrage.cpp \
    src/calibrationwindow.cpp

HEADERS  += src/mainwindow.h \
    src/server.h \
    src/debug.h \
    src/imu.h \
    src/dataholder.h \
    src/dataset.h \
    src/graph.h \
    src/curve.h \
    src/proxystrategy.h \
    src/serialport.h \
    src/acquisitionsettings.h \
    src/datasource.h \
    src/filtrage.h \
    src/calibrationwindow.h

FORMS    += src/IHM.ui

RESOURCES += \
    pictures.qrc






