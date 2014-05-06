#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <sstream>
#include <qwt_legend.h>
#include "mainwindow.h"
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

    addMenu();

    m_accelerations = new Graph({QString("acceleration_x"), QString("acceleration_y"), QString("acceleration_z")});
    m_accelerations->setTitle("Accelerations and angular velocity");

    m_angles = new Graph({QString("rolling"), QString("pitch"), QString("yaw")});
    m_angles->setTitle("Speed and angles");

    m_positions = new Graph({QString("position_x"), QString("position_y"), QString("position_z")});
    m_positions->setTitle("Positions");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_accelerations);
    layout->addWidget(m_angles);
    layout->addWidget(m_positions);

    ui->tabAccel->setLayout(layout);


    QObject::connect(actionOffset,SIGNAL(triggered()),this,SLOT(offset()));
    QObject::connect(Server::getInstance(), SIGNAL(ReceiveFromPeer(QString&)), this, SLOT(onNewData(QString&)));
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

void MainWindow::addMenu()
{
    menuFichier = menuBar()->addMenu("Fichier");
    menuOptions = menuBar()->addMenu("Option");

    actionOffset = menuOptions->addAction("Offset");
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
}
