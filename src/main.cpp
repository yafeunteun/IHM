#include <QApplication>
#include "mainwindow.h"
#include "server.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

//m_port = SerialPort::initPort("./.serial.conf");
    /*
    m_startSerial = new QAction("Start serial", this);
    connect(m_startSerial, SIGNAL(triggered()), m_port, SLOT(startReading()));
    connect(m_startSerial, SIGNAL(triggered()), this, SLOT(onStartReading()));
    Server* s = Server::getInstance();

void MainWindow::selectSerialPort()
{
    PortSelection *select = new PortSelection(m_port, this);
    select->exec();
}*/

    MainWindow w;
    w.show();

    return a.exec();
}
