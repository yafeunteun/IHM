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

void DataHolderProxy::addDataSet(std::initializer_list<QString> list) // verify unicity of the label
{
    for(QString label : list)
    {
        if(DataHolder::getInstance()->getDataSet(label) == nullptr)
        {
            DataHolder::getInstance()->addDataSet(label);
        }
    }
}

void DataHolderProxy::addData(QString& incommingRawData) // verify incomming data
{
    QVector<float> data;
    float n;
    QRegExp regex(" ", Qt::CaseInsensitive);
    QStringList tmp;
    bool ok = false;

    tmp = incommingRawData.split(regex, QString::SkipEmptyParts);

    for(QString number : tmp)
    {
        n = number.toFloat(&ok);
        if(ok){
            data.append(n);
        }
    }

    if(DataHolder::getInstance()->getSize() == data.size()){
        DataHolder::getInstance()->addData(data);
    }
}


DataSet* DataHolderProxy::getDataSet(const QString& label) // verify that the label exists in DataHolder::m_datasets
{
    return DataHolder::getInstance()->getDataSet(label);
}
