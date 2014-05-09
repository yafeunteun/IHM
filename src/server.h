#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "debug.h"

class Server: public QTcpServer
{
    Q_OBJECT
public:
    static Server* getInstance(void);
    QTcpSocket* getPeer(void){return m_peer;}
    void setPort(quint16 port){this->m_port = port;}
    void setAddress(QHostAddress addr){this->m_addr = addr;}

protected:
    static Server *instance;
    Server();
    ~Server();
    QTcpSocket* m_peer = nullptr;
    quint16 m_port = 0;
    QHostAddress m_addr;


public slots:
    void start();
    void stop();
    void resume();
    void dataAvailable(void);
    void onConnection(void);
    void onDisconnection(void);
    void sendToPeer(QString answer);

signals:
    void newData(QString&);
    void peerConnected(void);
    void peerDisconnected(void);
    void error(QString&);

};

#endif // SERVER_H




