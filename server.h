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

protected:
    static Server *instance;
    Server();
    ~Server();
    QTcpSocket* m_peer = nullptr;

public slots:
    void onDataReadyRead(void);
    void onConnection(void);
    void onDisconnection(void);
    void sendToPeer(QString answer);

signals:
    void ReceiveFromPeer(QString);
    void peerConnected(void);
    void peerDisconnected(void);

};

#endif // SERVER_H




