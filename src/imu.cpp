#include "imu.h"

IMU* IMU::instance = nullptr;

IMU* IMU::getInstance(void)
{
    if(IMU::instance == nullptr){
        instance = new IMU();
        return instance;
    }
    else{
        return IMU::instance;
    }
}


IMU::IMU()
{
}
