#ifndef SERVER_H
#define SERVER_H

/*!
 * \file server.h
 * \author yann feunteun
 * \version 0.1
 * \date 05/14/2014
 */

#include <QTcpServer>
#include <QTimer>
#include "debug.h"

/*! \class Server
* \brief This class represents the server.
* It implements a singleton pattern, you don't need to create an instance of this class.
* You just need to call getInstance() to get a pointer to the unique instance of this class.
* The first call will create the unique instance.
*/
class Server: public QTcpServer
{
    Q_OBJECT

public:
    static Server* getInstance(void);

    /*!
    *  \brief Returns a pointer on the peer connected to the server or nullptr if no peer is connected.
    */
    inline QTcpSocket* getPeer(void){return m_peer;}

    /*!
    *  \brief Sets the listening port.
    */
    inline void setPort(quint16 port){this->m_port = port;}

private:
    static Server *instance;
    Server();
    ~Server();
    QTcpSocket* m_peer = nullptr;
    quint16 m_port = 0;
    QHostAddress m_addr;

    QTimer * m_timer1;
    QTimer * m_timer2;
    static quint64 offsetW;
    static quint64 offsetR;
    static char* buffer;


public slots:
    void start();
    void stop();

private slots :
    void writeToFile(void);
    void readFromFile(void);
    void onConnection(void);

signals:
    /*!
    *  \brief [SIGNAL] This signal is emitted everytime an error occurs with the server.
    */
    void error(QString&);

    /*!
    *  \brief [SIGNAL] This signal is emitted everytime the status of the server changes.
    */
    void status(QString&, int);

    /*!
    *  \brief [SIGNAL] This signal is emitted everytime new data has been received on the server.
    */
    void newData(QString&);

};

#endif // SERVER_H




