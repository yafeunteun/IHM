#include "serialport.h"
#include "portselection.h"
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

    /* Reader Thread */
    Rthread = new QThread;
    Reader* reader = new Reader();
    reader->moveToThread(Rthread);
    connect(Rthread, SIGNAL(started()), reader, SLOT(process()));
    connect(reader, SIGNAL(finished()), Rthread, SLOT(quit()));
    connect(reader, SIGNAL(finished()), reader, SLOT(deleteLater()));
    connect(Rthread, SIGNAL(finished()), Rthread, SLOT(deleteLater()));

    m_timer = new QTimer();
    m_timer->setInterval(0);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(writeToFile()));

}

SerialPort::~SerialPort()
{
}

void SerialPort::start()
{

    if(!this->open(QIODevice::ReadWrite))
    {
        QString err("Can't open port with specified settings !");
        emit error(err);
    }

    else
    {
        m_timer->start();
        Rthread->start();
    }
}


void SerialPort::stop()
{
    m_timer->stop();
    this->close();
}

void SerialPort::resume()
{
    this->start();
}



void SerialPort::writeToFile(void)
{
    mutex.lock();

    QString read  = this->readAll();
    std::memcpy((void*)(buffer+offsetW), (void*)read.toUtf8().constData(), strlen(read.toUtf8().constData()));
    offsetW += strlen(read.toUtf8().constData());

    mutex.unlock();
}

void SerialPort::readFromFile(void)
{
    mutex.lock();

    static void *pointer = nullptr;
    char data[30];
    std::memset(data, '\0', 50);

    pointer = memchr(buffer+offsetR, '\r', offsetW);

    if(pointer != NULL){
        std::memcpy((void*)data, (void*)(buffer+offsetR), ((char*)pointer-(buffer+offsetR)));
        offsetR += (char*)pointer-(buffer+offsetR) + 2;

        QString tmp = QString::fromUtf8(data);
        DEBUG(tmp);
        //DataHolderProxy::getInstance()->addData(test);
    }

    mutex.unlock();

}

