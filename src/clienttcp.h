#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QTcpSocket>
#include <windows.h>

class ClientTcp : public QObject
{
Q_OBJECT
public :
    ClientTcp();
public slots :
    /** @remove **/ void recoit_IP(QString IP2);  // en provenance de l'IHM et se connecte au serveur
    void recoit_texte(QString t); // en provenance de l'IHM et écrit sur la socket
private slots :
    /** @remove **/ void connexion_OK();  // en provenance de la socket et émet un signal vers l'IHM
    /** @remove **/ void probleme_connexion();
    /** @remove **/ void lecture();       // en provenance de la socket, lit la socket, émet un signal vers l'IHM

public slots :
    void bPlayPressed();


signals :
    void vers_IHM_connexion_OK();
    void vers_IHM_connexion_NOTOK();
    void vers_IHM_texte(QString);
private :
    QString IP;
    int port;
    QTcpSocket soc;
};

#endif // CLIENTTCP_H
