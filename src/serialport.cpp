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

void SerialPort::startReading()
{

    if(!this->open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(0, "Error !", tr("Can't open port with specified settings !"));
    }

    else
    {
        m_timer->start();
        Rthread->start();
    }
}



void SerialPort::onDataReceived()
{
}

void SerialPort::stopReading()
{
    this->close();
    m_timer->stop();
}


SerialPort* SerialPort::initPort(const QString &filepath)
{
    std::ifstream fstream(filepath.toStdString(), std::ios::in);
    std::string data;
    SerialPort* port = new SerialPort();
    PortSelection *select = new PortSelection(nullptr);

    std::cout << filepath.toStdString() << std::endl;

    if (fstream){
        std::getline(fstream, data);
        QStringList tmp = QString(data.c_str()).split(";");

        port->setPortName(tmp[0]);
        std::cout << tmp[0].toStdString();
        std::cout << tmp[1].toStdString();
        std::cout << tmp[2].toStdString();
        std::cout << tmp[3].toStdString();
        std::cout << tmp[4].toStdString();
        std::cout << tmp[5].toStdString();
        port->setBaudRate(select->map_baud.find(tmp[1])->second);
        port->setDataBits(select->map_dataBits.find(tmp[2])->second);
        port->setFlowControl(select->map_flowControl.find(tmp[3])->second);
        port->setParity(select->map_parity.find(tmp[4])->second);
        port->setStopBits(select->map_stopBits.find(tmp[5])->second);
    }
    return port;
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

