#include "dataset.h"

DataSet::DataSet(QString &label)
{
    m_label = label;
}


void DataSet::addPoints(std::initializer_list<QPointF> list)
{
    for(QPointF pt : list)
    {
        m_points.append(pt);
        emit dataUpdated();
    }
}
