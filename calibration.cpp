#include "calibration.h"

void AccelerometerSensibilityAndOffset::doAlgorithm()
{
    DEBUG("Performing AccelerometerSensibilityAndOffset::doAlgorithm()");
}

void AccelerometerOrthogonality::doAlgorithm()
{
    DEBUG("Performing AccelerometerOrthogonality::doAlgorithm()");
}
void GyrometerOffset::doAlgorithm()
{
    DEBUG("Performing GyrometerOffset::doAlgorithm()");
}

void GyrometerSensibility::doAlgorithm()
{
    DEBUG("Performing GyrometerSensibility::doAlgorithm()");
}

void GyrometerOrthogonality::doAlgorithm()
{
    DEBUG("Performing GyrometerOrthogonality::doAlgorithm()");
}

void MagnetometerCalibration::doAlgorithm()
{
    DEBUG("Performing MagnetometerCalibration::doAlgorithm()");
}

Calibration* Calibration::getCalibrationStrategy(Calibration_t calibration)
{
    switch (calibration) {
    case ACCSensibilityAndOffset:
        return new AccelerometerSensibilityAndOffset();
        break;
    case ACCOrthogonality:
        return new AccelerometerOrthogonality();
        break;
    case GYROffset:
        return new GyrometerOffset();
        break;
    case GYRSensibility:
        return new GyrometerSensibility();
        break;
    case GYROrthogonality:
        return new GyrometerOrthogonality();
        break;
    case MAGCalibration:
        return new MagnetometerCalibration();
        break;
    default:
        return nullptr;
        break;
    }
}
