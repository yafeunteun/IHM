#include "proxystrategy.h"


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


QVector<float> NoProxy::doAlgorithm(QString& incommingRawData)
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.append(n);
        }
    }

    return data;
}

void NoProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}

QVector<float> AccelerometerProxy::doAlgorithm(QString& incommingRawData)
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;
    static float last_val[3] = {0.};
    static ushort pos = 0;
    const float ponder = 1./50.;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            float estimated = last_val[pos] + ponder * (n - last_val[pos]);
            last_val[pos++] = estimated;
            data.append(estimated);
            if(pos > 2){
                pos = 0;
            }
        }
    }

    return data;
}

void AccelerometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}


QVector<float> GyrometerProxy::doAlgorithm(QString& incommingRawData)
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;
    static float last_val[3] = {0.};
    static ushort pos = 0;
    const float ponder = 1./50.;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            float estimated = last_val[pos] + ponder * (n - last_val[pos]);
            last_val[pos++] = estimated;
            data.append(estimated);
            if(pos > 2){
                pos = 0;
            }
        }
    }

    return data;
}

void GyrometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}


QVector<float> MagnetometerProxy::doAlgorithm(QString& incommingRawData)
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;
    static float last_val[3] = {0.};
    static ushort pos = 0;
    const float ponder = 1./50.;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            float estimated = last_val[pos] + ponder * (n - last_val[pos]);
            last_val[pos++] = estimated;
            data.append(estimated);
            if(pos > 2){
                pos = 0;
            }
        }
    }

    return data;
}

void MagnetometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}


QVector<float> BarometerProxy::doAlgorithm(QString& incommingRawData)
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;
    static float last_val = 0.;
    const float ponder = 1./50.;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            float estimated = last_val + ponder * (n - last_val);
            last_val = estimated;
            data.append(estimated);
        }
    }

    return data;
}

void BarometerProxy::setConfiguration(QVector<QVariant>* configuration)
{
    /* Configure members with argument here if needed */
    /* nota : there is no member to configure yet, you need to add it if needed */
}


QVector<float> TermometerProxy::doAlgorithm(QString& incommingRawData)
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;
    static float last_val = 0.;
    const float ponder = 1./50.;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            float estimated = last_val + ponder * (n - last_val);
            last_val = estimated;
            data.append(estimated);
        }
    }

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



