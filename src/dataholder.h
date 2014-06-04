#ifndef DATAHOLDER_H
#define DATAHOLDER_H

/*!
 * \file dataholder.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */


#include "dataset.h"
#include "proxystrategy.h"

/*! \class DataHolder
   * \brief This class represents a data storage object and provides storage for several sets of data each.
   * It also furnishes methods to organize and to access the differents sets of data.
   */

class DataHolder
{
public:
    DataHolder(std::initializer_list<QString> list, ProxyStrategy::Proxy_t type = ProxyStrategy::NOPROXY);
    ~DataHolder();
    void addDataSet(QString &label);
    void addData(QString &&incommingRawData);
    DataSet* getDataSet(const QString& label);

    /*!
    *  \brief Return the number of DataSet contained in the object.
    */
    inline size_t getSize(){return m_datasets.size();}
private:
    ProxyStrategy* m_strategy;
    QVector<DataSet*> m_datasets;
};

#endif // DATAHOLDER_H




