#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "dataset.h"

class DataHolder
{
public:
    static DataHolder* getInstance(void);
    void addDataSet(QString &label);
    void addData(QVector<float> points);
    DataSet* getDataSet(const QString& label);
    int getSize(){return m_datasets.size();}
private:
    static DataHolder *instance;
    DataHolder();
    ~DataHolder();

    QVector<DataSet*> m_datasets;
};

#endif // DATAHOLDER_H




