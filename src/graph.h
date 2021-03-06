#ifndef GRAPH_H
#define GRAPH_H

/*!
 * \file graph.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QPushButton>
#include <QCheckBox>
#include <QVector>
#include <QStringList>
#include "curve.h"
#include "dataholder.h"

/*! \class Graph
   * \brief Graphical view of the data contained in a DataHolder object.
   */
class Graph : public QWidget
{
    Q_OBJECT
public:
    explicit Graph(std::initializer_list<QString> labels, DataHolder *source, QWidget *parent = 0 );
    void setTitle(const QString& title);

private:
    QwtPlot *m_plot;
    QVector<QPushButton*> m_buttons;
    QVector<QCheckBox*> m_checkboxes;
    QVector<Curve*> m_curves;
    int m_colorIndex = 13;
    DataHolder* m_source;
signals:

public slots:
    void curveDisplay(void);
    void changeColor(void);
    void update(void);
};


#endif // GRAPH_H
