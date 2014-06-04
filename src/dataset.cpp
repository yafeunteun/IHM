#include "dataset.h"
#include "src/debug.h"


/*!
*  \brief Constructor
*
*  Constructor of DataSet class
*
*  \param label : A QString describing the nature of the data for instance : velocity.
*  \param parent : Constructs a widget which is a child of parent.
*
*/
DataSet::DataSet(QString &label, QWidget *parent) : QWidget(parent)
{
    m_label = label;
}

/*!
    *  \brief Append a point to the object.
    *
    *  \param point : The ordinate of the point to add.
    */
void DataSet::addPoint(const float point)
{
    m_points.append({m_currentX++, point});
    emit dataUpdated();
}
