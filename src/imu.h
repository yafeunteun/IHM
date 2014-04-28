#ifndef IMU_H
#define IMU_H

#include "calibration.h"

class IMU
{
public:
    IMU();
    void setCalibration(Calibration* calibration){m_calibrationStrategy = calibration;}
    void calibrate(void){m_calibrationStrategy->doAlgorithm();}
private:
    Calibration* m_calibrationStrategy = nullptr;
};

#endif // IMU_H
