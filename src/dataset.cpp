#include "dataset.h"
#include "src/debug.h"

DataSet::DataSet(QWidget *parent) : QWidget(parent)
{
}

DataSet::DataSet(QString &label, QWidget *parent) : QWidget(parent)
{
    m_label = label;
    DEBUG("New dataset : " + m_label + ".\n");
}

DataSet::DataSet(const DataSet&) : QWidget()
{
}

void DataSet::addPoint(const float point)
{
    DEBUG("DataSet '" + this->m_label + "' point added (" + QString::number(m_currentX) + "," + QString::number(point) + ").\n");
    m_points.append({m_currentX++, point});
    emit dataUpdated();
}
