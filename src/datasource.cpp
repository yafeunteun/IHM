#include "datasource.h"
#include "debug.h"


DataSource* DataSource::instance = nullptr;

DataSource* DataSource::getInstance(void)
{
    if(DataSource::instance == nullptr){
        instance = new DataSource();
        return instance;
    }
    else{
        return DataSource::instance;
    }
}

void DataSource::start()
{
    if(!m_configured)
    {
        QString err("You must configure the source before !");
        error(err);
        return;
    }

    if(m_source == AcquisitionSettings::SERIAL_PORT){
        SerialPort::getInstance()->start();
    }else{
        Server::getInstance()->start();
    }
}

void DataSource::stop()
{
    if(m_source == AcquisitionSettings::SERIAL_PORT){
        SerialPort::getInstance()->stop();
    }else{
        Server::getInstance()->stop();
    }
}

void DataSource::resume()
{

}

void DataSource::configure(AcquisitionSettings::Type_t type, QVector<QVariant> parameters)
{
    m_source = type;
    m_configured = true;

    if(m_source == AcquisitionSettings::SERIAL_PORT)
    {
        DEBUG("Configuring serial port");
        SerialPort* instance = SerialPort::getInstance();
        instance->setPortName(parameters[0].toString());
        instance->setBaudRate(*(reinterpret_cast<BaudRateType*>(&parameters[1])));
        instance->setDataBits(*(reinterpret_cast<DataBitsType*>(&parameters[2])));
        instance->setFlowControl(*(reinterpret_cast<FlowType*>(&parameters[3])));
        instance->setParity(*(reinterpret_cast<ParityType*>(&parameters[4])));
        instance->setStopBits(*(reinterpret_cast<StopBitsType*>(&parameters[5])));


    }else if(m_source == AcquisitionSettings::SERVER){
        DEBUG("Configuring server");
        Server::getInstance()->setPort(parameters[0].toInt());
    }

}

void DataSource::onError(QString& err)
{
    emit error(err);
}

