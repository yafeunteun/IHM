#include "curve.h"


/*!
    *  \brief Constructor
    *
    *  Constructor of Curve class
    *
    *  \param set : A pointer to the DataSet object the curve will be connected to.
    *  \param color : The color of the curve.
    *
    */
Curve::Curve(DataSet * set, QColor color) :
    QwtPlotCurve()
{
    m_dataSet = set;

    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);

    this->setSamples(m_dataSet->getPoints());

}


/*!
    *  \brief Allows to update the curve by adding the points currently held by the DataSet object the instance is connected to.
    */
void Curve::updateCurve()
{
    this->setSamples(m_dataSet->getPoints());
}

/*!
*  \brief Change the color of the curve.
*
*  \param color : The new color of the curve.
*/
void Curve::setColor(QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}
