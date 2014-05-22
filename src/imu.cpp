#include "imu.h"
#include "datasource.h"

IMU* IMU::instance = nullptr;

IMU* IMU::getInstance(void)
{
    if(IMU::instance == nullptr){
        instance = new IMU();
        return instance;
    }
    else{
        return IMU::instance;
    }
}


IMU::IMU()
{
    QObject::connect(SerialPort::getInstance(), SIGNAL(newData(QString&)), this, SLOT(recordData(QString&)));
    QObject::connect(Server::getInstance(), SIGNAL(newData(QString&)), this, SLOT(recordData(QString&)));

    DEBUG("Slots connected in IMU contructor");

    m_accelerometers = new DataHolder({QString("x_axis"), QString("y_axis"), QString("z_axis")}, ProxyStrategy::ACC);
    m_gyrometers = new DataHolder({QString("x_axis"), QString("y_axis"), QString("z_axis")}, ProxyStrategy::GYR);
    m_magnetometers = new DataHolder({QString("x_axis"), QString("y_axis"), QString("z_axis")}, ProxyStrategy::MGN);
    m_barometer = new DataHolder({QString("pressure")}, ProxyStrategy::BRM);
    m_termometer = new DataHolder({QString("temperature")}, ProxyStrategy::TMP);
}


void IMU::onStartRecordData()
{
    DataSource::getInstance()->start();
}

void IMU::onStopRecordData()
{
    DataSource::getInstance()->stop();
}


void IMU::recordData(QString& data)
{
    DEBUG("Data received in IMU (for data recording) : " + data);

    if(m_rawData.size() < m_rawData.max_size())
    {
        m_rawData.push_back(data);
    }

    /* splitting the incomming dta here and distribute it between all the dataHolders */
    m_accelerometers->addData(data.section(" ", 0, 2));
    m_gyrometers->addData(data.section(" ", 3, 5));
    m_magnetometers->addData(data.section(" ", 6, 8));
    m_barometer->addData(data.section(" ", 9, 9));
    m_termometer->addData(data.section(" ", 10, 10));

    emit dataUpdated();

}

void IMU::onStartCalibratePressure()
{
    QObject::disconnect(SerialPort::getInstance(), SIGNAL(newData(QString&)), this, SLOT(recordData(QString&)));
    QObject::disconnect(Server::getInstance(), SIGNAL(newData(QString&)), this, SLOT(recordData(QString&)));

    QObject::connect(SerialPort::getInstance(), SIGNAL(newData(QString&)), this, SLOT(calibratePressure(QString&)));
    QObject::connect(Server::getInstance(), SIGNAL(newData(QString&)), this, SLOT(calibratePressure(QString&)));

    DataSource::getInstance()->start();
}

void IMU::calibratePressure(QString &data)
{
    DEBUG("Data received in IMU (pressure calibration) : " + data);
    /* Doing something with the data received */
    emit calibrationFinished();
    DEBUG("Pressure sensor has been calibrated");

    DataSource::getInstance()->stop();
}
