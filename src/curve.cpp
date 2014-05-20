#include "curve.h"

Curve::Curve(DataSet * set, QColor color) :
    QwtPlotCurve()
{
    m_dataSet = set;

    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);

    this->setSamples(m_dataSet->getPoints());

}

/* All the data are stored but only one out of ten is displayed */
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
