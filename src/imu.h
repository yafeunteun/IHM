#ifndef IMU_H
#define IMU_H

/*!
 * \file datasource.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <QObject>
#include "dataholder.h"


/*! \class IMU
* \brief This class represents the Inertial Movement Unit.
* It implements a singleton pattern, you don't need to create an instance of this class.
* You just need to call getInstance() to get a pointer to the unique instance of this class.
* The first call will create the unique instance.
* From this class you can acces to all the data recorded from all the sensors of the inertial unit.
*/
class IMU : public QObject
{
    Q_OBJECT

public:
    static IMU* getInstance(void);
    /*!
    *  \brief Return a pointer to the DataHolder linked to the accelerometers.
    */
    inline DataHolder* getAccelerometersData(){return m_accelerometers;}
    /*!
    *  \brief Return a pointer to the DataHolder linked to the gyrometers.
    */
    inline DataHolder* getGyrometersData(){return m_gyrometers;}
    /*!
    *  \brief Return a pointer to the DataHolder linked to the magnetometers.
    */
    inline DataHolder* getMagnetometersData(){return m_magnetometers;}
    /*!
    *  \brief Return a pointer to the DataHolder linked to the barometer.
    */
    inline DataHolder* getBarometerData(){return m_barometer;}
    /*!
    *  \brief Return a pointer to the DataHolder linked to the termometer.
    */
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
    void onStartCalibrate();
    void calibrate(QString& data);
    void save(QString& folder);
signals:
    /*!
    *  \brief [SIGNAL] This signal is emitted each time new data have been processed and added to the right DataHolders).
    */
    void dataUpdated();

    /*!
    *  \brief [SIGNAL] This signal is emitted each time new data have been filtered for calibration.
    */
    void newCalibratedData(std::vector<float>&); /* emitted each time a new set of data has been filtered */

};

#endif // IMU_H
