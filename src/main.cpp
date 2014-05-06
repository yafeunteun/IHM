#include <QApplication>
#include "mainwindow.h"
#include "server.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);


    Server* s = Server::getInstance();

    MainWindow w;
    w.show();

    return a.exec();
}
