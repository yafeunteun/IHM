#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include <QPointF>
#include "dataset.h"
#include "qwt_plot_curve.h"


class Curve : public QObject, public QwtPlotCurve
{
    Q_OBJECT
public:
    explicit Curve(DataSet* set, QColor color,  QObject*parent=0);
    void setColor(QColor &color);
private:
    DataSet* m_dataSet;
signals:

public slots:
    void updateCurve(void);

};

#endif // CURVE_H
