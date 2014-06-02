#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QWidget>
#include <QLabel>

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
