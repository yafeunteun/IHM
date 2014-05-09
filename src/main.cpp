#include <QApplication>
#include "mainwindow.h"
#include "acquisitionsettings.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

    MainWindow w;
    AcquisitionSettings test(NULL);
    test.show();

   // w.show();

    return a.exec();
}
