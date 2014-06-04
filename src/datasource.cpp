#include "datasource.h"
#include "debug.h"


DataSource* DataSource::instance = nullptr;


/*!
*  \brief Return a pointer to the unique instance of the class.
*  Create a unique instance before returning it if this method is called for the first time.
*/
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

/*!
*  \brief [SLOT] Begin data acquisition if a source has been properly set.
*/
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

/*!
*  \brief [SLOT] Stop data acquisition.
*/
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


/*!
*  \brief [SLOT] Congigure the data source
*
*  This slot must be exclusiely used connected to the signal newConfiguration of the class AcquisitionSettings.
*
*  \param type : The type of the data source. Can be SerialPort or Server.
*  \param parameters : A vector containing the parameters used to configure the data source.
*/
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

/*!
*  \brief [SLOT] Emit a signal describing the last error thrown by the data source.
*/
void DataSource::onError(QString& err)
{
    emit error(err);
}

