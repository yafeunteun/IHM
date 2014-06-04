#include "dataholder.h"


/*!
    *  \brief Constructor
    *
    *  Constructor of DataHolder class
    *
    *  \param list : A list of strings. Each string defines the label of a set of data. For instance let's say you want to store
    * 3D points (i.e 3 vectors of data: x, y, z), the list could be {"x", "y", "z"}. If so, 3 sets will be created with the corresponding
    * label.
    *
    * \param type : The ProxyStrategy associated with the DataHolder, when data will be added to the instance, the
    * data will be filtered before using the ProxyStrategy associated to the type chosen. See ProxyStrategy documentation for more.
    *
    */
DataHolder::DataHolder(std::initializer_list<QString> list, ProxyStrategy::Proxy_t type)
{

    m_strategy = ProxyStrategy::getProxy(type);

    for(QString label : list)
    {
        if(this->getDataSet(label) == nullptr)
        {
            this->addDataSet(label);
        }
    }
}

/*!
*  \brief Destructor
*
*  Destructor of DataHolder class

*/
DataHolder::~DataHolder()
{
    delete m_strategy;
}


/*!
*  \brief Append a DataSet to the instance.
*
*  \param label : A string describing the nature of the data stored by the DataSet added.
*/
void DataHolder::addDataSet(QString &label)
{
    m_datasets.push_back(new DataSet(label));
}




/*!
    *  \brief Appends data to the sets stores.
    *
    *  The data are given as a QString object which will be parsed by the ProxyStrategy chosen and added to the differents sets.
    *
    *  \param incommingRawData : A string containing the data to parse and add.
    *
    */
void DataHolder::addData(QString&& incommingRawData)
{
    std::vector<float> data = m_strategy->doAlgorithm(incommingRawData);

    if(getSize() == data.size()){
        for(unsigned index = 0; index < data.size(); ++index)
        {
            m_datasets[index]->addPoint(data[index]);
        }
    }
}


/*!
    *  \brief Get access to the DataSet(s) contained in the instance.
    *
    *  \param label : A string describing the DataSet you want to get access to.
    *
    *  \return A pointer to the DataSet corresponding to the label given.
    *
    */
DataSet* DataHolder::getDataSet(const QString& label)
{

    for(auto it = m_datasets.begin(); it != m_datasets.end(); ++it)
    {
        if((*it)->getLabel() == label)
            return *it;
    }

    return nullptr;
}
