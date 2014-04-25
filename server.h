#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

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
    void onNewAnswer(QString answer);

signals:
    void newQuery(QString);
    void peerConnected(void);
    void peerDisconnected(void);

};

#endif // SERVER_H




