#ifndef SERIALPORT_H
#define SERIALPORT_H

/*!
 * \file serialport.h
 * \author yann feunteun
 * \version 0.1
 * \date 05/14/2014
 */

#include <map>
#include <string>
#include <QTimer>
#include "qextserialport.h"
#include "debug.h"

using std::map;
using std::string;


/*! \class SerialPort
* \brief This class represents the serial port.
* It implements a singleton pattern, you don't need to create an instance of this class.
* You just need to call getInstance() to get a pointer to the unique instance of this class.
* The first call will create the unique instance.
*/
class SerialPort : public QextSerialPort
{
    Q_OBJECT
public:
    static SerialPort* getInstance(void);
private:
    SerialPort();
    ~SerialPort();
    static SerialPort *instance;
    QTimer * m_timer1;
    QTimer * m_timer2;
    static quint64 offsetW;
    static quint64 offsetR;
    static char* buffer;

private slots:
    void writeToFile(void);
    void readFromFile(void);

public slots:
    void start();
    void stop();

signals:
    /*!
    *  \brief [SIGNAL] This signal is emitted everytime an error occurs with the serial port.
    */
    void error(QString&);

    /*!
    *  \brief [SIGNAL] This signal is emitted everytime the status of the serial port changes.
    */
    void status(QString&, int);

    /*!
    *  \brief [SIGNAL] This signal is emitted everytime new data has been received on the serial port.
    */
    void newData(QString&);



};



#endif // SERIALPORT_H
