#ifndef IMU_H
#define IMU_H

#include <QObject>
#include "dataholder.h"

class IMU : public QObject
{
    Q_OBJECT

public:
    static IMU* getInstance(void);
    inline DataHolder* getAccelerometersData(){return m_accelerometers;}
    inline DataHolder* getGyrometersData(){return m_gyrometers;}
    inline DataHolder* getMagnetometersData(){return m_magnetometers;}
    inline DataHolder* getBarometerData(){return m_barometer;}
private:
    IMU();
    static IMU *instance;

    DataHolder* m_accelerometers;
    DataHolder* m_gyrometers;
    DataHolder* m_magnetometers;
    DataHolder* m_barometer;

    std::vector<QString> m_rawData; /* It will allow to save raw data in a file with a call to save() method */

public slots:
    void onStartRecordData();
    void onStopRecordData();
    void recordData(QString& data);
    void onStartCalibratePressure();
    void calibratePressure(QString& data);
signals:
    void dataUpdated();
    void calibrationFinished();

};

#endif // IMU_H
