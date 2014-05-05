#ifndef DATASET_H
#define DATASET_H

#include <QVector>
#include <QWidget>
#include <QPointF>

class DataSet : public QWidget
{
    Q_OBJECT

public:
    explicit DataSet(QWidget *parent = 0);
    DataSet(QString& label, QWidget *parent = 0);
    explicit DataSet(const DataSet&);
    DataSet& operator =(const DataSet&);
    void addPoint(const float point);
    QVector<QPointF>& getPoints(){return m_points;}
    int getSize(){return m_points.size();}
    QString& getLabel(){return m_label;}
    void setLabel(const QString &label){m_label = label;}
private:
    QVector<QPointF> m_points;
    QString m_label;
    float m_currentX = 0;
signals:
    void dataUpdated(); // emitted each time data are appended to m_points with a call to addPoints()

};

#endif // DATASET_H
