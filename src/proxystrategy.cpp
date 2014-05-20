#include "proxystrategy.h"


ProxyStrategy* ProxyStrategy::getProxy(Proxy_t type)
{
    switch(type){
    case NOFILTER:
        return new NoFilter();
        break;
    default:
        return nullptr;
    }
}



QVector<float> NoFilter::doAlgorithm(QString& incommingRawData)
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

void NoFilter::setConfiguration(QVector<QVariant>* configuration)
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
