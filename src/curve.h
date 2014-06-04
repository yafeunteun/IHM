#ifndef CURVE_H
#define CURVE_H

/*!
 * \file curve.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */


#include <QWidget>
#include <QPointF>
#include "dataset.h"
#include "qwt_plot_curve.h"


/*! \class Curve
   * \brief This class represents a curve. It is connected to a DataSet object in order to update itself.
   * The color can be chosen.
   */
class Curve : public QObject, public QwtPlotCurve
{
    Q_OBJECT
public:
    explicit
    Curve(DataSet* set, QColor color);
    void setColor(QColor &color);
private:
    DataSet* m_dataSet;
signals:

public slots:
    void updateCurve(void);

};

#endif // CURVE_H
