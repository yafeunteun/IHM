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
    inline DataHolder* getTermometerData(){return m_termometer;}
private:
    IMU();
    static IMU *instance;

    DataHolder* m_accelerometers;
    DataHolder* m_gyrometers;
    DataHolder* m_magnetometers;
    DataHolder* m_barometer;
    DataHolder* m_termometer;

    std::vector<QString> m_rawData; /* It will allow to save raw data in a file with a call to save() method */

    const QString c_prefixFolderName = "imu_data_";
    const QString c_rawDataFileName = "raw.csv";
    const QString c_accDataFileName = "acc.csv";
    const QString c_gyrDataFileName = "gyr.csv";
    const QString c_magDataFileName = "mag.csv";
    const QString c_barDataFileName = "bar.csv";
    const QString c_tmpDataFileName = "tmp.csv";

public slots:
    void onStartRecordData();
    void onStopRecordData();
    void recordData(QString& data);
    void onStartCalibratePressure();
    void calibratePressure(QString& data);
    void save(QString& folder);
signals:
    void dataUpdated();
    void calibrationFinished();

};

#endif // IMU_H
