#include "serialport.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <ios>
#include <cstring>
#include "debug.h"

using std::ofstream;
using std::ifstream;
using std::ios;

SerialPort* SerialPort::instance = nullptr;
quint64 SerialPort::offsetR = 0;
quint64 SerialPort::offsetW = 0;
char* SerialPort::buffer = new char[10000000]; /* 10^7 bytes */

SerialPort* SerialPort::getInstance(void)
{
    if(SerialPort::instance == nullptr){
        instance = new SerialPort();
        return instance;
    }
    else{
        return SerialPort::instance;
    }
}


SerialPort::SerialPort()
{
    m_timer1 = new QTimer();
    m_timer1->setInterval(5);

    m_timer2 = new QTimer();
    m_timer2->setInterval(5);

    connect(m_timer1, SIGNAL(timeout()), this, SLOT(writeToFile()));
    connect(m_timer2, SIGNAL(timeout()), this, SLOT(readFromFile()));
}

SerialPort::~SerialPort()
{
}


void SerialPort::start()
{
    QString stat = "Trying to open serial port " + this->portName();
    DEBUG(stat);
    emit status(stat, 10000);


    if(!this->open(QIODevice::ReadWrite))
    {
        QString err("Can't open port with specified settings !");
        emit status(err, 10000);
        emit error(err);
    }

    else
    {
        m_timer1->start();
        m_timer2->start();
    }
}


void SerialPort::stop()
{
    QString stat = "Record has been stopped.";
    emit status(stat, 10000);
    m_timer1->stop();
    m_timer2->stop();
    this->close();
}

void SerialPort::resume()
{
    this->start();
}



void SerialPort::writeToFile(void)
{

    QString read  = this->readAll();
    std::memcpy((void*)(buffer+offsetW), (void*)read.toUtf8().constData(), strlen(read.toUtf8().constData()));
    offsetW += strlen(read.toUtf8().constData());
}

void SerialPort::readFromFile(void)
{
    static void *pointer = nullptr;
    char data[50];
    std::memset(data, '\0', 50);

    pointer = memchr(buffer+offsetR, '\r', offsetW);

    if(pointer != NULL){
        std::memcpy((void*)data, (void*)(buffer+offsetR), ((char*)pointer-(buffer+offsetR)));
        offsetR += (char*)pointer-(buffer+offsetR) + 2;

        QString tmp = QString::fromUtf8(data);
        emit newData(tmp);
    }

}

