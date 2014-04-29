#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "dataset.h"

class DataHolder
{
public:
    static DataHolder* getInstance(void);
    void addDataSet(std::initializer_list<QString&>);
    void addData(QVector<QPointF>& points);
    DataSet& getDataSet(const QString& label);
private:
    static DataHolder *instance;
    DataHolder();
    ~DataHolder();

    QVector<DataSet> m_datasets;
};

#endif // DATAHOLDER_H




