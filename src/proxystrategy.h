#ifndef PROXYSTRATEGY_H
#define PROXYSTRATEGY_H

#include <QVector>
#include <QVariant>
#include <QString>

class ProxyStrategy
{
public:
    typedef enum{NOPROXY, ACC, MGN, GYR, BRM, TMP}Proxy_t;

    ProxyStrategy(){}
    ~ProxyStrategy(){}
    virtual QVector<float> doAlgorithm(QString& incommingRawData) = 0;
    virtual void setConfiguration(QVector<QVariant>* configuration) = 0;
    static ProxyStrategy* getProxy(Proxy_t type);

protected:
};


class NoProxy : public ProxyStrategy
{
public:
    NoProxy(){}
    ~NoProxy(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};

class AccelerometerProxy : public ProxyStrategy
{
public:
    AccelerometerProxy(){}
    ~AccelerometerProxy(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};

class GyrometerProxy : public ProxyStrategy
{
public:
    GyrometerProxy(){}
    ~GyrometerProxy(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};

class MagnetometerProxy : public ProxyStrategy
{
public:
    MagnetometerProxy(){}
    ~MagnetometerProxy(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};

class BarometerProxy : public ProxyStrategy
{
public:
    BarometerProxy(){}
    ~BarometerProxy(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};

class TermometerProxy : public ProxyStrategy
{
public:
    TermometerProxy(){}
    ~TermometerProxy(){}
    QVector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};




#endif // PROXYSTRATEGY_H
