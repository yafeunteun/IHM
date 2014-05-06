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
