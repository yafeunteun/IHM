#ifndef DATASET_H
#define DATASET_H

/*!
 * \file dataset.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <QVector>
#include <QWidget>
#include <QPointF>


/*! \class DataSet
   * \brief This class represents a data storage object for QPointF. It can be regarded as an augmented vector.
   */
class DataSet : public QWidget
{
    Q_OBJECT

public:
    DataSet(QString& label, QWidget *parent = 0);
    void addPoint(const float point);

    /*!
    *  \brief Return a reference on the container used to store the data
    */
    inline QVector<QPointF>& getPoints(){return m_points;}

    /*!
    *  \brief Return the number of points stored.
    */
    inline size_t getSize(){return m_points.size();}

    /*!
    *  \brief Return the label of the object.
    */
    inline const QString& getLabel(){return m_label;}
private:
    QVector<QPointF> m_points;
    QString m_label;
    float m_currentX = 0;
signals:
    /*!
    *  \brief [SIGNAL] Emitted each time data are appended to the object with a call to addPoints()
    */
    void dataUpdated();

};

#endif // DATASET_H
