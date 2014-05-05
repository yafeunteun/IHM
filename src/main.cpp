#include <QApplication>
#include "mainwindow.h"
#include "server.h"

#include "dataholderproxy.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);


    Server* s = Server::getInstance();
    DataHolderProxy *proxy = DataHolderProxy::getInstance();


    proxy->addDataSet({QString("acceleration_x"),
                       QString("acceleration_y"),
                       QString("acceleration_z"),
                       QString("rolling"),
                       QString("pitch"),
                       QString("yaw"),
                       QString("position_x"),
                       QString("position_y"),
                       QString("position_z")});

    MainWindow w;
    w.show();

    return a.exec();
}
