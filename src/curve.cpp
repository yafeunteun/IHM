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

/* All the data are stored but only one out of ten is displayed */
void Curve::updateCurve()
{
    //static int i = 0;
    //if(i >= 10){             /* Displays one point out of 10 */
        this->setSamples(m_dataSet->getPoints());
       // i = 0;
  //  }
   // ++i;
}


void Curve::setColor(QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}
