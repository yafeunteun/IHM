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
void DataHolder::addDataSet(QString &label)
{
    m_datasets.push_back(new DataSet(label));
}

void DataHolder::addData(QVector<float> points)
{
    for(int index = 0; index < points.size(); ++index)
    {
        m_datasets[index]->addPoint(points[index]);
    }
}

DataSet* DataHolder::getDataSet(const QString& label)
{

    for(auto it = m_datasets.begin(); it != m_datasets.end(); ++it)
    {
        if((*it)->getLabel() == label)
            return *it;
    }

    return nullptr;
}
