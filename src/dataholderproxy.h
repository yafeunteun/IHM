#ifndef DATAHOLDERPROXY_H
#define DATAHOLDERPROXY_H

#include "dataholder.h"

class DataHolderProxy
{
public:
    static DataHolderProxy* getInstance(void);
    void addDataSet(std::initializer_list<QString> list); // verify unicity of the label
    void addData(QString& incommingRawData); // verify incomming data
    DataSet* getDataSet(const QString& label); // verify that the label exists in DataHolder::m_datasets
    int getSize(){return DataHolder::getInstance()->getSize();}
private:
    static DataHolderProxy *instance;
    DataHolderProxy();
    ~DataHolderProxy();
};

#endif // DATAHOLDERPROXY_H