#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>
#include <cstring>
#include "server.h"

Server* Server::instance = nullptr;
quint64 Server::offsetR = 0;
quint64 Server::offsetW = 0;
char* Server::buffer = new char[10000000]; /* 10^7 bytes */


/*!
*  \brief Return a pointer to the unique instance of the class.
*  Create a unique instance before returning it if this method is called for the first time.
*/
Server* Server::getInstance(void)
{
    if(Server::instance == nullptr){
        instance = new Server();
        return instance;
    }
    else{
        return Server::instance;
    }
}

Server::Server()
{
    m_timer1 = new QTimer();
    m_timer1->setInterval(5);

    m_timer2 = new QTimer();
    m_timer2->setInterval(5);

    connect(m_timer1, SIGNAL(timeout()), this, SLOT(writeToFile()));
    connect(m_timer2, SIGNAL(timeout()), this, SLOT(readFromFile()));

    m_addr = QHostAddress::Any;
}

Server::~Server()
{
}

/*!
*  \brief Starts reading on the serial port.
*/
void Server::start()
{    
    QString stat = "Trying to start the server...";
    status(stat, 10000);

    if(m_port != this->serverPort()) /* if port has been changed */
    {
        this->close();
    }


    if(!this->listen(m_addr, m_port))
    {
        if(this->isListening())
        {
            stat = "Server is still listening";
            status(stat, 10000);

        }else{

            QString err = this->errorString();
            stat = "Starting server failed !";
            status(stat, 10000);
            emit error(err);
        }
    }else{
        stat = "Server is listening on " + m_addr.toString() + ":" + QString::number(m_port);
        DEBUG(stat);
        status(stat, 10000);
        QObject::connect(this, SIGNAL(newConnection()), this, SLOT(onConnection()));
        m_timer1->start();
        m_timer2->start();
    }
}

/*!
*  \brief Stops reading on the serial port.
*/
void Server::stop()
{
    m_timer1->stop();
    m_timer2->stop();
}


void Server::writeToFile(void)
{
    if(m_peer != nullptr){
        QString read  = m_peer->readAll();
        std::memcpy((void*)(buffer+offsetW), (void*)read.toUtf8().constData(), strlen(read.toUtf8().constData()));
        offsetW += strlen(read.toUtf8().constData());
    }
}

void Server::readFromFile(void)
{
    static void *pointer = nullptr;
    char data[100];
    std::memset(data, '\0', 100);

    pointer = memchr(buffer+offsetR, '\r', offsetW);

    if(pointer != NULL){
        std::memcpy((void*)data, (void*)(buffer+offsetR), ((char*)pointer-(buffer+offsetR)));
        offsetR += (char*)pointer-(buffer+offsetR) + 2;

        QString tmp = QString::fromUtf8(data);
        emit newData(tmp);
    }

}

void Server::onConnection()
{
    QTcpSocket *sock = this->nextPendingConnection();
    m_peer = sock;
    DEBUG("Peer connected : " + sock->peerAddress().toString());
    QString stat = "Peer connected : " + sock->peerAddress().toString();
    emit status(stat, 10000);
}





