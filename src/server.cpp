#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>
#include "server.h"

Server* Server::instance = nullptr;

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
        CRITICAL_ERROR("Unable to listen !");
    }

    DEBUG("Server is listening on " + this->serverAddress().toString() + ":" + QString::number(this->serverPort()));
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
    DEBUG("Peer connected : " + sock->peerAddress().toString());
}

void Server::onDataReadyRead(void)
{
    QString query = m_peer->readAll();
    DEBUG("Message from " + m_peer->peerAddress().toString() + " : " + query);
    emit ReceiveFromPeer(query);
}


void Server::onDisconnection(void)
{
    emit peerDisconnected();
}

void Server::sendToPeer(QString answer)
{
    if(m_peer!=nullptr && m_peer->isWritable()){
        answer = answer.trimmed();
        answer.append("\r\n");
        m_peer->write(answer.toUtf8());
    }
}



