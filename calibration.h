#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "src/debug.h"

class Calibration
{
public:
    typedef enum {
        ACCSensibilityAndOffset,
        ACCOrthogonality,
        GYROffset,
        GYRSensibility,
        GYROrthogonality,
        MAGCalibration
                 }Calibration_t;

    Calibration(){}
    virtual void doAlgorithm() = 0;
    static Calibration* getCalibrationStrategy(Calibration_t calibration);

};


class AccelerometerSensibilityAndOffset : public Calibration
{
public:
    AccelerometerSensibilityAndOffset(){}
    void doAlgorithm();
};

class AccelerometerOrthogonality : public Calibration
{
public:
    AccelerometerOrthogonality(){}
    void doAlgorithm();
};

class GyrometerOffset : public Calibration
{
public:
    GyrometerOffset(){}
    void doAlgorithm();
};

class GyrometerSensibility : public Calibration
{
public:
    GyrometerSensibility(){}
    void doAlgorithm();
};

class GyrometerOrthogonality : public Calibration
{
public:
    GyrometerOrthogonality(){}
    void doAlgorithm();
};

class MagnetometerCalibration : public Calibration
{
public:
    MagnetometerCalibration(){}
    void doAlgorithm();
};

#endif // CALIBRATION_H
