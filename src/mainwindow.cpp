#include <QMessageBox>
#include <QFileDialog>
#include <QToolBar>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include "mainwindow.h"
#include "serialport.h"
#include "acquisitionsettings.h"
#include "server.h"
#include "imu.h"
#include "calibrationwindow.h"


/*!
*  \brief Constructor
*
*  Constructor of MainWindow class
*
*  \param parent : Constructs a widget which is a child of parent.
*
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), parent(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenu();
    createStatusBar();
    createToolBar();


    m_accelerations = new Graph({QString("x_axis"), QString("y_axis"), QString("z_axis")},
                                IMU::getInstance()->getAccelerometersData());
    m_accelerations->setTitle("Accelerations and angular velocity");

    m_angles = new Graph({QString("x_axis"), QString("y_axis"), QString("z_axis")},
                         IMU::getInstance()->getGyrometersData());
    m_angles->setTitle("Speed and angles");

    m_positions = new Graph({QString("x_axis"), QString("y_axis"), QString("z_axis")},
                            IMU::getInstance()->getMagnetometersData());
    m_positions->setTitle("Positions");

    m_pressure = new Graph({QString("pressure")},
                           IMU::getInstance()->getBarometerData());
    m_pressure->setTitle("Pressure");

    m_temperature = new Graph({QString("temperature")},
                           IMU::getInstance()->getTermometerData());
    m_temperature->setTitle("Temperature");

    ui->tabMaster->addTab(m_accelerations, "Accelerometers");
    ui->tabMaster->addTab(m_angles, "Gyrometers");
    ui->tabMaster->addTab(m_positions, "Magnetometers");
    ui->tabMaster->addTab(m_pressure, "Pressure");
    ui->tabMaster->addTab(m_temperature, "Temperature");

    QObject::connect(Server::getInstance(), SIGNAL(error(QString&)), this, SLOT(onError(QString&)));
    QObject::connect(SerialPort::getInstance(), SIGNAL(error(QString&)), this, SLOT(onError(QString&)));
    QObject::connect(SerialPort::getInstance(), SIGNAL(status(QString&, int)), this, SLOT(onStatusChanged(QString&,int)));
    QObject::connect(Server::getInstance(), SIGNAL(status(QString&, int)), this, SLOT(onStatusChanged(QString&,int)));
    QObject::connect(IMU::getInstance(), SIGNAL(dataUpdated()), this, SLOT(updateView()));
    /* the view is updated each time the tab changed */
    QObject::connect(ui->tabMaster, SIGNAL(currentChanged(int)), this, SLOT(updateView()));
}

/*!
*  \brief Destructor
*
*  Destructor of MainWindow class
*
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
*  \brief Builds the menu bar.
*/
void MainWindow::createMenu()
{
    QMenu* fileMenu = new QMenu("Files");
    this->menuBar()->addMenu(fileMenu);

    fileMenu->addAction(m_saveRecordedData);
    fileMenu->addAction(m_loadRecordedData);
    fileMenu->addSeparator();
    fileMenu->addAction(m_saveConfiguration);
    fileMenu->addSeparator();
    fileMenu->addAction(m_loadSensorData);
    fileMenu->addSeparator();
    fileMenu->addAction(m_quit);

    QMenu* viewMenu = new QMenu("&View");
    this->menuBar()->addMenu(viewMenu);

    viewMenu->addAction(m_eraseCurve);

    QMenu* studyMenu = new QMenu("&Study");
    this->menuBar()->addMenu(studyMenu);

    studyMenu->addAction(m_startRecord);
    studyMenu->addAction(m_stopRecord);
    studyMenu->addSeparator();
    studyMenu->addAction(m_drawSpeed);
    studyMenu->addAction(m_drawPosition);

    QMenu* configurationMenu = new QMenu("&Configuration");
    this->menuBar()->addMenu(configurationMenu);

    configurationMenu->addAction(m_selectSource);
    configurationMenu->addSeparator();
    configurationMenu->addAction(m_calibrate);


    QMenu* helpMenu = new QMenu("Help");
    this->menuBar()->addMenu(helpMenu);

    helpMenu->addAction(m_manual);
    helpMenu->addSeparator();
    helpMenu->addAction(m_about);


}

/*!
*  \brief Makes the connections between the items of the menu bar and the actions associated.
*/
void MainWindow::createActions(void)
{

    /* File */
    m_saveRecordedData = new QAction("Save recorded data", this);
    connect(m_saveRecordedData, SIGNAL(triggered()), this, SLOT(onSaveRecordedData()));

    m_loadRecordedData = new QAction("Load recorded data", this);
    m_saveConfiguration = new QAction("Save configuration", this);
    m_loadSensorData = new QAction("Load sensor data", this);

    m_quit = new QAction("&Quit", this);
    m_quit->setShortcut(QKeySequence("Ctrl+Q"));
    m_quit->setIcon(QIcon(":/pictures/quit.png"));
    connect(m_quit, SIGNAL(triggered()), this, SLOT(close()));


    /* View */
    m_eraseCurve = new QAction("Erase Curve", this);

    /* Study */
    m_startRecord = new QAction("Start record", this);
    connect(m_startRecord, SIGNAL(triggered()), IMU::getInstance(), SLOT(onStartRecordData()));
    m_startRecord->setIcon(QIcon(":/pictures/startRecord.png"));
    //connect(m_startRecord, SIGNAL(triggered(bool)), m_startRecord, SLOT(setEnabled(bool)));

    m_stopRecord = new QAction("Stop record", this);
    m_stopRecord->setIcon(QIcon(":/pictures/stopRecord.png"));
    connect(m_stopRecord, SIGNAL(triggered()), IMU::getInstance(), SLOT(onStopRecordData()));

    m_drawSpeed = new QAction("Draw speed", this);
    m_drawPosition = new QAction("Draw position", this);

    /* Configuration */
    m_selectSource = new QAction("Select source", this);
    m_selectSource->setIcon(QIcon(":/pictures/selectSource"));
    connect(m_selectSource, SIGNAL(triggered()), this, SLOT(selectSource()));

    m_calibrate = new QAction("Calibrate", this);
    connect(m_calibrate, SIGNAL(triggered()), this, SLOT(onCalibrate()));

    /* Help */
    m_manual = new QAction("&Manual", this);
    connect(m_manual, SIGNAL(triggered()), this, SLOT(openManual()));

    m_about = new QAction("&About", this);
    connect(m_about, SIGNAL(triggered()), this, SLOT(about()));

}

/*!
*  \brief Initialize the status bar with a message.
*/
void MainWindow::createStatusBar()
{
    this->statusBar()->showMessage("test status bar");
}

/*!
*  \brief Builds the tool bar.
*/
void MainWindow::createToolBar()
{
    QToolBar* fileToolbar = addToolBar("File");
    fileToolbar->addAction(m_quit);

    QToolBar* configToolbar = addToolBar("Configuration");
    configToolbar->addAction(m_selectSource);

    QToolBar* studyToolbar = addToolBar("Study");
    studyToolbar->addAction(m_startRecord);
    studyToolbar->addAction(m_stopRecord);
}

void MainWindow::selectSource()
{
    AcquisitionSettings* settings = new AcquisitionSettings();
    settings->show();
}



void MainWindow::onError(QString& err)
{
    QMessageBox::warning(this, "Error", err);
}


void MainWindow::onStatusChanged(QString& stat, int timeout)
{
    this->statusBar()->showMessage(stat, timeout);
}


void MainWindow::about()
{
    QMessageBox::information(this, "About", "Version 0.8\nStill in Developpement\nIn case of problem please contact the author at yannfeunteun@gmail.com\n");
}


void MainWindow::updateView()
{
    DEBUG("Update View");
    int current = ui->tabMaster->currentIndex();

    switch(current){
    case 0:
        DEBUG("Update Accelerometers");
        m_accelerations->update();
        break;
    case 1:
        DEBUG("Update Gyrometers");
        m_angles->update();
        break;
    case 2:
        DEBUG("Update Magnetometers");
        m_positions->update();
        break;
    case 3:
        DEBUG("Update pressure");
        m_pressure->update();
        break;
    case 4:
        DEBUG("Update temperature");
        m_temperature->update();
        break;
    default:
        DEBUG("THIS MESSAGE MAY NOT BE DISPLAYED CHECK 'void MainWindow::updateView()'");
    }
}

void MainWindow::onSaveRecordedData()
{
    QString folder = QFileDialog::getExistingDirectory(this, "Choose a folder");
    if(!folder.isEmpty()){
        IMU::getInstance()->save(folder);
    }
}

void MainWindow::onCalibrate()
{
    IMU::getInstance()->onStartCalibrate();
    CalibrationWindow *win = new CalibrationWindow();
    win->show();
}

void MainWindow::openManual()
{
    QDir indexFolder;
    indexFolder.setPath("./site");
    QString absolutePath = indexFolder.absolutePath();
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(absolutePath + "/index.html")))
    {
        QMessageBox::warning(this, "Error", "The root of the manual's website must be in the same folder as this program.");
    }
}
