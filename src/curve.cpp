#include "curve.h"

Curve::Curve(DataSet * set, QColor color, QObject *parent) :
    QwtPlotCurve(), QObject(parent)
{
    m_dataSet = set;
    QObject::connect(m_dataSet, SIGNAL(dataUpdated()), this, SLOT(updateCurve()));

    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);

    this->setSamples(m_dataSet->getPoints());

}

void Curve::updateCurve()
{
    this->setSamples(m_dataSet->getPoints());
}


void Curve::setColor(QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}
