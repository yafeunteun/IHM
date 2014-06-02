#ifndef PROXYSTRATEGY_H
#define PROXYSTRATEGY_H

#include <QVector>
#include <QVariant>
#include <QString>

#include "filtrage.h"

class ProxyStrategy
{
public:
    typedef enum{NOPROXY, ACC, MGN, GYR, BRM, TMP}Proxy_t;

    ProxyStrategy(){}
    virtual ~ProxyStrategy(){}
    virtual std::vector<float>  doAlgorithm(QString& incommingRawData) = 0;
    virtual void setConfiguration(QVector<QVariant>* configuration) = 0;
    static ProxyStrategy* getProxy(Proxy_t type);

protected:
};


class NoProxy : public ProxyStrategy
{
public:
    NoProxy(){}
    ~NoProxy(){}
    std::vector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
};

class AccelerometerProxy : public ProxyStrategy
{
public:
    AccelerometerProxy(){m_filtrage = new Filtrage(3); m_filtrage->setK(0.02);}
    ~AccelerometerProxy(){}
    std::vector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
private:
    Filtrage *m_filtrage;
};

class GyrometerProxy : public ProxyStrategy
{
public:
    GyrometerProxy(){m_filtrage = new Filtrage(3); m_filtrage->setK(0.02);}
    ~GyrometerProxy(){}
   std::vector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
private:
    Filtrage *m_filtrage;
};

class MagnetometerProxy : public ProxyStrategy
{
public:
    MagnetometerProxy(){m_filtrage = new Filtrage(3); m_filtrage->setK(0.02);}
    ~MagnetometerProxy(){}
    std::vector<float> doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
private:
    Filtrage *m_filtrage;
};

class BarometerProxy : public ProxyStrategy
{
public:
    BarometerProxy(){m_filtrage = new Filtrage(1); m_filtrage->setK(0.02);}
    ~BarometerProxy(){}
    std::vector<float>  doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
private:
    Filtrage *m_filtrage;
};

class TermometerProxy : public ProxyStrategy
{
public:
    TermometerProxy(){m_filtrage = new Filtrage(1); m_filtrage->setK(0.02);}
    ~TermometerProxy(){}
    std::vector<float>  doAlgorithm(QString& incommingRawData);
    void setConfiguration(QVector<QVariant>* configuration);
private:
    Filtrage *m_filtrage;
};




#endif // PROXYSTRATEGY_H
