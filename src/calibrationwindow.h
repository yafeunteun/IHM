#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

/*!
 * \file calibrationwindow.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <QWidget>
#include <QTableWidget>


/*! \class CalibrationWindow
* \brief This class represents the graphical widget allowing to calibrate the sensors of the inertial unit and the barometer.
*/
class CalibrationWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CalibrationWindow(QWidget *parent = 0);

signals:

public slots:
    void onNewCalibratedData(std::vector<float>&);

private:
    QTableWidget* m_accelerometers;
    QTableWidget* m_gyrometers;
    QTableWidget* m_magnetometers;
    QTableWidget* m_barTemp;


};

#endif // CALIBRATIONWINDOW_H
