#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "dataset.h"
#include "proxystrategy.h"

class DataHolder
{
public:
    DataHolder(std::initializer_list<QString> list, ProxyStrategy::Proxy_t type = ProxyStrategy::NOFILTER);
    ~DataHolder();
    inline void setProxy(ProxyStrategy::Proxy_t type){m_strategy = ProxyStrategy::getProxy(type);}
    void addDataSet(QString &label);
    void addData(QString &&incommingRawData);
    DataSet* getDataSet(const QString& label);
    int getSize(){return m_datasets.size();}
private:
    ProxyStrategy* m_strategy;
    QVector<DataSet*> m_datasets;
};

#endif // DATAHOLDER_H




