#ifndef DATAHOLDERPROXY_H
#define DATAHOLDERPROXY_H

#include "dataholder.h"

class DataHolderProxy
{
public:
    static DataHolderProxy* getInstance(void);
private:
    static DataHolderProxy *instance;
    DataHolderProxy();
    ~DataHolderProxy();
};

#endif // DATAHOLDERPROXY_H
