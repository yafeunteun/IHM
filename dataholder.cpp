#include "dataholder.h"


DataHolder* DataHolder::instance = nullptr;

DataHolder* DataHolder::getInstance(void)
{
    if(DataHolder::instance == nullptr){
        instance = new DataHolder();
        return instance;
    }
    else{
        return DataHolder::instance;
    }
}

DataHolder::DataHolder()
{
}
