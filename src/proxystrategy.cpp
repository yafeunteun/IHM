#include "proxystrategy.h"
#include "debug.h"

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






/* calibrate(QString data)
 * {
 *      static int i = 0;
 *      static int sum = 0;
 *      bool ok = false;
 *
 *      float m = data.toFloat(&ok);
 *      if(ok){
 *          sum += m;
 *          ++i;
 *      }
 *      if(i == 10)
 *      {
 *          i=0;
 *          m_offset = sum / 10.;
 *          emit calibrationFinished();  Tells the Graph object to send the next data to the DataHolder.
 *      }
 * }
 * */



