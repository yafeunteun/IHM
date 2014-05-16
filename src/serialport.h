#ifndef SERIALPORT_H
#define SERIALPORT_H
#include "qextserialport.h"
#include <map>
#include <iostream>
#include <string>
#include <QTimer>
#include "debug.h"



using std::map;
using std::string;

class SerialPort : public QextSerialPort
{
    Q_OBJECT
public:
    static SerialPort* getInstance(void);
private:
    QTimer * m_timer1;
    QTimer * m_timer2;
    static quint64 offsetW;
    static quint64 offsetR;
    static char* buffer;

public slots:
    void start();
    void stop();
    void resume();
    void writeToFile(void);
    void readFromFile(void);

signals:
    void error(QString&);
    void status(QString&, int);
    void newData(QString&);

private:
    SerialPort();
    ~SerialPort();
    static SerialPort *instance;

};



#endif // SERIALPORT_H
