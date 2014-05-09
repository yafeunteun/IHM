#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <sstream>
#include <qwt_legend.h>
#include "mainwindow.h"
#include "serialport.h"
#include "portselection.h"
#include "acquisitionsettings.h"
#include "acquisitionsettingsproxy.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), parent(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWoffset = new QMainWindow;
    QOffset = new QWidget();

    QWoffset->setWindowTitle("Offsets");
    QWoffset->setCentralWidget(QOffset);

    createActions();
    createMenu();


    m_accelerations = new Graph({QString("acceleration_x"), QString("acceleration_y"), QString("acceleration_z")});
    m_accelerations->setTitle("Accelerations and angular velocity");

    m_angles = new Graph({QString("rolling"), QString("pitch"), QString("yaw")});
    m_angles->setTitle("Speed and angles");

    m_positions = new Graph({QString("position_x"), QString("position_y"), QString("position_z")});
    m_positions->setTitle("Positions");

    m_pressure = new Graph({QString("pressure")});
    m_pressure->setTitle("Pressure");

    ui->tabMaster->addTab(m_accelerations, "Accelerometers");
    ui->tabMaster->addTab(m_angles, "Gyrometers");
    ui->tabMaster->addTab(m_positions, "Magnetometers");
    ui->tabMaster->addTab(m_pressure, "Pressure");

    QObject::connect(Server::getInstance(), SIGNAL(newData(QString&)), this, SLOT(onNewData(QString&)));
    QObject::connect(SerialPort::getInstance(), SIGNAL(newData(QString&)), this, SLOT(onNewData(QString&)));
    QObject::connect(Server::getInstance(), SIGNAL(error(QString&)), this, SLOT(onError(QString&)));
    QObject::connect(SerialPort::getInstance(), SIGNAL(error(QString&)), this, SLOT(onError(QString&)));
}




void MainWindow::offset()
{
    if (QWoffset->isVisible())
        QWoffset->hide();
    else
        QWoffset->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu()
{
    QMenu* menuFiles = new QMenu("Files");
    this->menuBar()->addMenu(menuFiles);

    menuFiles->addSeparator();
    menuFiles->addAction(m_configureSource);
    menuFiles->addAction(m_startAcquisition);
    menuFiles->addAction(m_stopAcquisition);
    menuFiles->addSeparator();

}

 void MainWindow::createActions(void)
 {
     m_configureSource = new QAction("Select source", this);
     connect(m_configureSource, SIGNAL(triggered()), this, SLOT(selectSource()));

     m_startAcquisition = new QAction("Start acquisition", this);
     connect(m_startAcquisition, SIGNAL(triggered()), AcquisitionSettingsProxy::getInstance(), SLOT(start()));

     m_stopAcquisition = new QAction("Stop acquisition", this);
     connect(m_stopAcquisition, SIGNAL(triggered()), AcquisitionSettingsProxy::getInstance(), SLOT(stop()));
 }

 void MainWindow::selectSource()
 {
     AcquisitionSettings* settings = new AcquisitionSettings();
     settings->show();
 }



/** @todo
 * Méthode qui sera à ajouter au proxy
 * */
double MainWindow::doubleintegration(double acc){
    double vitesse;
    double position;

    vitesse=acc*1.01;
    //a=d/t
    position=vitesse*1.01;
    //v=d/t
    return position;
}

void MainWindow::onNewData(QString& data)
{
    /* save raw Data in a file here */
    m_accelerations->addData(data.section(" ", 0, 2));
    m_angles->addData(data.section(" ", 3, 5));
    m_positions->addData(data.section(" ", 6, 8));
    m_pressure->addData(data.section(" ", 9));
}

void MainWindow::onError(QString& err)
{
    QMessageBox::warning(this, "Error", err);
}
