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
}

Server::~Server()
{
}

void Server::start()
{
    if(!this->listen(this->serverAddress(), this->serverPort()))
    {
        QString err = this->errorString();
        emit error(err);
    }else{
        DEBUG("Server is listening on " + this->serverAddress().toString() + ":" + QString::number(this->serverPort()));
        QObject::connect(this, SIGNAL(newConnection()), this, SLOT(onConnection()));
    }
}

void Server::stop()
{
    if(m_peer != nullptr){
        this->disconnect(m_peer, SIGNAL(readyRead()), this, SLOT(onDataReadyRead()));
    }else{
        QString err("No peer connected");
        emit error(err);
    }
}

void Server::resume()
{
    if(m_peer != nullptr){
        this->connect(m_peer, SIGNAL(readyRead()), this, SLOT(onDataReadyRead()));
    }else{
        QString err("No peer connected");
        emit error(err);
    }
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




