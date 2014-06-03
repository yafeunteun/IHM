#include "calibrationwindow.h"
#include "imu.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>

/*!
    *  \brief Constructor
    *
    *  Constructor of AcquisitionSettings class
    *
    *  \param parent : Constructs a widget which is a child of parent.
    */
CalibrationWindow::CalibrationWindow(QWidget *parent):
    QWidget(parent)
{
    m_accX = new QLabel;
    m_accY = new QLabel;
    m_accZ = new QLabel;
    m_gyrX = new QLabel;
    m_gyrY = new QLabel;
    m_gyrZ = new QLabel;
    m_magX = new QLabel;
    m_magY = new QLabel;
    m_magZ = new QLabel;
    m_pressure = new QLabel;
    m_temperature = new QLabel;

    QFormLayout* accLayout = new QFormLayout;
    QFormLayout* gyrLayout = new QFormLayout;
    QFormLayout* magLayout = new QFormLayout;
    QFormLayout* barLayout = new QFormLayout;

    accLayout->addRow("x_axis", m_accX);
    accLayout->addRow("y_axis", m_accY);
    accLayout->addRow("z_axis", m_accZ);
    gyrLayout->addRow("x_axis", m_gyrX);
    gyrLayout->addRow("y_axis", m_gyrY);
    gyrLayout->addRow("z_layout", m_gyrZ);
    magLayout->addRow("x_axis", m_magX);
    magLayout->addRow("y_axis", m_magY);
    magLayout->addRow("z_axis", m_magZ);
    barLayout->addRow("Pressure", m_pressure);
    barLayout->addRow("Temperature", m_temperature);

    QGroupBox *accBox = new QGroupBox;
    QGroupBox *gyrBox = new QGroupBox;
    QGroupBox *magBox = new QGroupBox;
    QGroupBox *barBox = new QGroupBox;

    accBox->setLayout(accLayout);
    gyrBox->setLayout(gyrLayout);
    magBox->setLayout(magLayout);
    barBox->setLayout(barLayout);

    QVBoxLayout *global = new QVBoxLayout;
    global->addWidget(accBox);
    global->addWidget(gyrBox);
    global->addWidget(magBox);
    global->addWidget(barBox);

    this->setLayout(global);
    connect(IMU::getInstance(), SIGNAL(newCalibratedData(std::vector<float>&)), this, SLOT(onNewCalibratedData(std::vector<float>&)));
}


/*!
    *  \brief Performed each time new data has been calibrated.
    *
    *  Update every label with the new value received. There is a label for each sensor.
    *
    *  \param data : A vector containing the new calibrated data.
    */
void CalibrationWindow::onNewCalibratedData(std::vector<float>& data)
{
    if(data.size() == 11){
        m_accX->setText(QString::number(data[0]));
        m_accY->setText(QString::number(data[1]));
        m_accZ->setText(QString::number(data[2]));
        m_gyrX->setText(QString::number(data[3]));
        m_gyrY->setText(QString::number(data[4]));
        m_gyrZ->setText(QString::number(data[5]));
        m_magX->setText(QString::number(data[6]));
        m_magY->setText(QString::number(data[7]));
        m_magZ->setText(QString::number(data[8]));
        m_pressure->setText(QString::number(data[9]));
        m_temperature->setText(QString::number(data[10]));
    }
}
