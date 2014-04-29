#ifndef DATASET_H
#define DATASET_H

#include <QVector>
#include <QObject>
#include <QPointF>
#include <initializer_list>

using std::initializer_list;

class DataSet : public QObject
{
    Q_OBJECT

public:
    DataSet(QString& label);
    void addPoints(std::initializer_list<QPointF> list);
    QVector<QPointF>& getPoints(){return m_points;}
    int getSize(){return m_points.size();}
    QString& getLabel(){return m_label;}
private:
    QVector<QPointF> m_points;
    QString m_label;
signals:
    void dataUpdated(); // emitted each time data are appended to m_points with a call to addPoints()

};

#endif // DATASET_H
