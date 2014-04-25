#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>
#include "server.h"

Server* Server::instance = nullptr;


using std::endl;
using std::cout;


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
    quint16 port = 5000;
    listen(QHostAddress::LocalHost, port);
    if(!this->isListening())
    {
        QMessageBox::critical(0, "Error !", "Unable to listen !");
    }

    QObject::connect(this, SIGNAL(newConnection()), this, SLOT(onConnection()));
}

Server::~Server()
{
}

void Server::onConnection()
{
    QTcpSocket *sock = this->nextPendingConnection();
    m_peer = sock;
    QObject::connect(m_peer, SIGNAL(readyRead()), this, SLOT(onDataReadyRead()));
    emit peerConnected();
}

void Server::onDataReadyRead(void)
{
    QString query = m_peer->readAll();
    emit newQuery(query);
}


void Server::onDisconnection(void)
{
    emit peerDisconnected();
}

void Server::onNewAnswer(QString answer)
{
    if(m_peer!=nullptr && m_peer->isWritable()){
        answer = answer.trimmed();
        answer.append("\r\n");
        m_peer->write(answer.toUtf8());
    }
}



