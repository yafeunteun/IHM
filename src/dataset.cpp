#include "dataset.h"
#include "src/debug.h"

DataSet::DataSet(QWidget *parent) : QWidget(parent)
{
}

DataSet::DataSet(QString &label, QWidget *parent) : QWidget(parent)
{
    m_label = label;
}

DataSet::DataSet(const DataSet&) : QWidget()
{
}

void DataSet::addPoint(const float point)
{
    m_points.append({m_currentX++, point});
    emit dataUpdated();
}
