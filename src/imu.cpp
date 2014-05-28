#include "imu.h"
#include "datasource.h"
#include <QDateTime>
#include <iostream>
#include <fstream>
#include <QDir>

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

void IMU::save(QString &folder)
{
    DEBUG("Trying to save data");
    QString f = c_prefixFolderName + QString::number(QDateTime::currentMSecsSinceEpoch());

    /* Create destination path */
    QDir dir(folder);
    if(!dir.mkpath(folder+"/"+f))
    {
        DEBUG("Unable to create destination folder please check 'void IMU::save(QString &folder)'");
    }

    std::ofstream fraw;
    std::ofstream facc;
    std::ofstream fgyr;
    std::ofstream fmag;
    std::ofstream fbar;
    std::ofstream ftmp;

    fraw.open((folder+"/"+f+"/"+c_rawDataFileName).toStdString());
    facc.open((folder+"/"+f+"/"+c_accDataFileName).toStdString());
    fgyr.open((folder+"/"+f+"/"+c_gyrDataFileName).toStdString());
    fmag.open((folder+"/"+f+"/"+c_magDataFileName).toStdString());
    fbar.open((folder+"/"+f+"/"+c_barDataFileName).toStdString());
    ftmp.open((folder+"/"+f+"/"+c_tmpDataFileName).toStdString());

    /* writing data into files */

    /* raw data */
    for(QString d:m_rawData){
        QStringList values = d.split(' ');
        for(QString& v:values){
            fraw << v.toStdString() + ";";
        }

        fraw << std::endl;
    }

    /* accelerometers data */
    auto acc_x = m_accelerometers->getDataSet("x_axis")->getPoints();
    auto acc_y = m_accelerometers->getDataSet("y_axis")->getPoints();
    auto acc_z = m_accelerometers->getDataSet("z_axis")->getPoints();
    facc << "x_axis;" << "y_axis;" << "z_axis" << std::endl;
    for(quint64 index = 0; index < acc_x.size(); ++index){
        facc << QString::number(acc_x[index].y()).toStdString() << ";"
             << QString::number(acc_y[index].y()).toStdString() << ";"
             << QString::number(acc_z[index].y()).toStdString() << std::endl;
    }

    /* gyrometers data */
    auto gyr_x = m_gyrometers->getDataSet("x_axis")->getPoints();
    auto gyr_y = m_gyrometers->getDataSet("y_axis")->getPoints();
    auto gyr_z = m_gyrometers->getDataSet("z_axis")->getPoints();
    fgyr << "x_axis;" << "y_axis;" << "z_axis" << std::endl;
    for(quint64 index = 0; index < gyr_x.size(); ++index){
        fgyr << QString::number(gyr_x[index].y()).toStdString() << ";"
             << QString::number(gyr_y[index].y()).toStdString() << ";"
             << QString::number(gyr_z[index].y()).toStdString() << std::endl;
    }

    /* magnetometers data */
    auto mag_x = m_magnetometers->getDataSet("x_axis")->getPoints();
    auto mag_y = m_magnetometers->getDataSet("y_axis")->getPoints();
    auto mag_z = m_magnetometers->getDataSet("z_axis")->getPoints();
    fmag << "x_axis;" << "y_axis;" << "z_axis" << std::endl;
    for(quint64 index = 0; index < mag_x.size(); ++index){
        fmag << QString::number(mag_x[index].y()).toStdString() << ";"
             << QString::number(mag_y[index].y()).toStdString() << ";"
             << QString::number(mag_z[index].y()).toStdString() << std::endl;
    }

    /* barometer data */
    auto bar = m_barometer->getDataSet("pressure")->getPoints();
    fbar << "pressure" << std::endl;
    for(quint64 index = 0; index < bar.size(); ++index){
        fbar << QString::number(bar[index].y()).toStdString() << std::endl;
    }

    /* termometer data */
    auto tmp = m_termometer->getDataSet("temperature")->getPoints();
    ftmp << "temperature" << std::endl;
    for(quint64 index = 0; index < tmp.size(); ++index){
        ftmp << QString::number(tmp[index].y()).toStdString() << std::endl;
    }

    /* closing file streams */

    fraw.close();
    facc.close();
    fgyr.close();
    fmag.close();
    fbar.close();
    ftmp.close();
}
