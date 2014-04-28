#include "dataholderproxy.h"

DataHolderProxy* DataHolderProxy::instance = nullptr;

DataHolderProxy* DataHolderProxy::getInstance(void)
{
    if(DataHolderProxy::instance == nullptr){
        instance = new DataHolderProxy();
        return instance;
    }
    else{
        return DataHolderProxy::instance;
    }
}

DataHolderProxy::DataHolderProxy()
{
}

