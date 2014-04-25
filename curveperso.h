#ifndef CURVEPERSO_H
#define CURVEPERSO_H

#include "qwt_plot_curve.h"
#include <QCheckBox>
#include <QMainWindow>
#include "qwt_plot.h"
#include <QFile>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>

class CurvePerso : public QObject
{
Q_OBJECT
public:
    QwtPlot *plot;
    QwtPlotCurve *curve;
    QCheckBox *CB;
    QSpinBox *offsetSpin;
    QLabel *offsetLabel;
    QHBoxLayout *layoutOffset;
    QVector<double> data;
    QFile *saveFile;
    int offset;

    CurvePerso(QString name, QColor color, QString nameCB, int offset);
    ~CurvePerso();
    QCheckBox *getCB();
    void attachPerso(QwtPlot *plot);
    void setSamplesPerso(QVector<double> tmp);
    void addData(double point);
    void clearData();
    void saveCurve(QFile&);
    QHBoxLayout *getOffsetLayout();

private slots :
    void setVisibleCurve(int);
    void setOffset(int);
};

#endif // CURVEPERSO_H
