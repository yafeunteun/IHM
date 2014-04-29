#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "dataset.h"

class DataHolder
{
public:
    static DataHolder* getInstance(void);
private:
    static DataHolder *instance;
    DataHolder();
    ~DataHolder();
};

#endif // DATAHOLDER_H




