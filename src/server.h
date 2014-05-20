#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTimer>
#include "debug.h"

class Server: public QTcpServer
{
    Q_OBJECT

public:
    static Server* getInstance(void);
    QTcpSocket* getPeer(void){return m_peer;}
    void setPort(quint16 port){this->m_port = port;}

protected:
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
    void resume();
    void writeToFile(void);
    void readFromFile(void);
    void onConnection(void);
    void sendToPeer(QString answer);


signals:
    void newData(QString&);
    void status(QString&, int);
    void error(QString&);

};

#endif // SERVER_H




