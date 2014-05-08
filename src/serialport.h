#ifndef SERIALPORT_H
#define SERIALPORT_H
#include "qextserialport.h"
#include <map>
#include <iostream>
#include <string>
#include <QMutex>
#include <QTimer>
#include <QThread>
#include "debug.h"



using std::map;
using std::string;

class SerialPort : public QextSerialPort
{
    Q_OBJECT
public:
    static SerialPort* getInstance(void);
    static SerialPort* initPort(const QString &filepath);
    void readFromFile(void);

private:
    QTimer * m_timer;
    static quint64 offsetW;
    static quint64 offsetR;
    static char* buffer;
    QMutex mutex;

public slots:
    void startReading();
    void stopReading();
    void onDataReceived();
    void writeToFile(void);

signals:

private:
    SerialPort();
    ~SerialPort();
    QThread* Rthread;
    static SerialPort *instance;




};

class Reader : public QObject {
    Q_OBJECT

public:
    Reader(){}
    ~Reader(){}

public slots:
    inline void process(){
        while(1){
            SerialPort::getInstance()->readFromFile();
        }
        emit finished();
    }

signals:
    void finished();
};


#endif // SERIALPORT_H
