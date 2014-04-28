#ifndef IMU_H
#define IMU_H

#include "calibration.h"

class IMU
{
public:
    static IMU* getInstance(void);
    void setCalibration(Calibration* calibration){m_calibrationStrategy = calibration;}
    void calibrate(void){if(m_calibrationStrategy != nullptr){ m_calibrationStrategy->doAlgorithm();}
                        else{FATAL_ERROR("(SEGFAULT)In class IMU => m_calibrationStrategy is nullptr\n");}}
private:
    static IMU *instance;
    Calibration* m_calibrationStrategy = nullptr;
    IMU();
};

#endif // IMU_H
