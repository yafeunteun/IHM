#include <QApplication>
#include "mainwindow.h"
#include "server.h"
#include "serialport.h"
#include "acquisitionsettings.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

    SerialPort::getInstance()->initPort("./.serial.conf");

    MainWindow w;
    AcquisitionSettings test(NULL);
    test.show();

   // w.show();

    return a.exec();
}
