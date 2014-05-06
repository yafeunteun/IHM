#ifndef PROXYSTRATEGY_H
#define PROXYSTRATEGY_H

#include <QVector>
#include <QVariant>
#include <QString>

class ProxyStrategy
{
public:
    typedef enum{NOFILTER}Proxy_t;

    ProxyStrategy(){}
    ~ProxyStrategy(){}
    virtual QVector<float> doAlgorithm(QString& incommingRawData) = 0;
    virtual void setConfiguration(QVector<QVariant>* configuration) = 0;
    static ProxyStrategy* getProxy(Proxy_t type);

protected:
};


class NoFilter : public ProxyStrategy
{
public:
    NoFilter(){}
    ~NoFilter(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};


#endif // PROXYSTRATEGY_H
