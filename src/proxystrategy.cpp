#include "proxystrategy.h"
#include "debug.h"

/*!
*  \brief Returns a pointer on a ProxyStrategy subclass according to the type passing in parameter.
*  \param type : The type of proxy you want to get i.e. a subclass of ProxyStrategy.
*/
ProxyStrategy* ProxyStrategy::getProxy(Proxy_t type)
{

    switch(type){
    case NOPROXY:
        return new NoProxy();
        break;
    case ACC:
        return new AccelerometerProxy();
        break;
    case GYR:
        return new GyrometerProxy();
        break;
    case MGN:
        return new MagnetometerProxy();
        break;
    case BRM:
        return new BarometerProxy();
        break;
    case TMP:
        return new TermometerProxy();
    default:
        return nullptr;
    }
}


/*!
*  \brief This type of proxy doesn't modify the raw data.
*   It can be useful for passing it by parameter when required by a function where you don't want to modify the data.
*  \param incommingRawData : The raw data to process.
*  \return Returns the data processed.
*/
std::vector<float> NoProxy::doAlgorithm(QString& incommingRawData)
{
    std::vector<float>  data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.push_back(n);
        }
    }

    return data;
}


void NoProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}


/*!
*  \brief This type of proxy is used to process data comming from the accelerometers.
*  \param incommingRawData : The raw data to process.
*  \return Returns the data processed
*/
std::vector<float> AccelerometerProxy::doAlgorithm(QString& incommingRawData)
{
    std::vector<float>  data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.push_back(n);
        }
    }

    m_filtrage->passeBasRecur(data);
    return data;
}

void AccelerometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}

/*!
*  \brief This type of proxy is used to process data comming from the gyrometers.
*  \param incommingRawData : The raw data to process.
*  \return Returns the data processed
*/
std::vector<float> GyrometerProxy::doAlgorithm(QString& incommingRawData)
{
    std::vector<float>  data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.push_back(n);
        }
    }

    m_filtrage->passeBasRecur(data);
    return data;
}

void GyrometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}


/*!
*  \brief This type of proxy is used to process data comming from the magnetometers.
*  \param incommingRawData : The raw data to process.
*  \return Returns the data processed
*/
std::vector<float> MagnetometerProxy::doAlgorithm(QString& incommingRawData)
{
    std::vector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.push_back(n);
        }
    }

    m_filtrage->passeBasRecur(data);
    return data;
}

void MagnetometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}

/*!
*  \brief This type of proxy is used to process data comming from the barometer.
*  \param incommingRawData : The raw data to process.
*  \return Returns the data processed
*/
std::vector<float> BarometerProxy::doAlgorithm(QString& incommingRawData)
{
    std::vector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.push_back(n);
        }
    }

    m_filtrage->passeBasRecur(data);
    return data;
}

void BarometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}

/*!
*  \brief This type of proxy is used to process data comming from the termometer.
*  \param incommingRawData : The raw data to process.
*  \return Returns the data processed
*/
std::vector<float> TermometerProxy::doAlgorithm(QString& incommingRawData)
{
    std::vector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;


    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.push_back(n);
        }
    }

    m_filtrage->passeBasRecur(data);

    return data;
}

void TermometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}

