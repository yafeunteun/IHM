#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

/*!
 * \file calibrationwindow.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <QWidget>
#include <QLabel>


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
    QLabel *m_accX;
    QLabel *m_accY;
    QLabel *m_accZ;

    QLabel *m_gyrX;
    QLabel *m_gyrY;
    QLabel *m_gyrZ;

    QLabel *m_magX;
    QLabel *m_magY;
    QLabel *m_magZ;

    QLabel *m_pressure;
    QLabel *m_temperature;


};

#endif // CALIBRATIONWINDOW_H
