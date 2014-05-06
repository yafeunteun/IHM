#include "dataholder.h"



DataHolder::DataHolder(std::initializer_list<QString> list, ProxyStrategy::Proxy_t type)
{

    m_strategy = new NoFilter();

    for(QString label : list)
    {
        if(this->getDataSet(label) == nullptr)
        {
            this->addDataSet(label);
        }
    }
}

DataHolder::~DataHolder()
{
    delete m_strategy;
}

void DataHolder::addDataSet(QString &label)
{
    m_datasets.push_back(new DataSet(label));
}

void DataHolder::addData(QString& incommingRawData)
{
    QVector<float> data = m_strategy->doAlgorithm(incommingRawData);

    if(getSize() == data.size()){
        for(int index = 0; index < data.size(); ++index)
        {
            m_datasets[index]->addPoint(data[index]);
        }
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
