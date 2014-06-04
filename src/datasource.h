#ifndef DATASOURCE_H
#define DATASOURCE_H

/*!
 * \file datasource.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <QObject>
#include "serialport.h"
#include "server.h"
#include "acquisitionsettings.h"


/*! \class DataSource
* \brief This class implements a proxy pattern for both the SerialPort and the Server classes.
* Since it also implements a singleton pattern, you don't need to create an instance of this class.
* You just need to call getInstance() to get a pointer to the unique instance of this class.
* The first call will create the unique instance.
*/
class DataSource : public QObject
{
    Q_OBJECT

public:
    static DataSource* getInstance(void);
private:
    DataSource(){}
    ~DataSource(){}
    static DataSource *instance;
    bool m_configured = false;
    AcquisitionSettings::Type_t m_source;
public slots:
    void start();
    void stop();
    void resume();
    void configure(AcquisitionSettings::Type_t type, QVector<QVariant> parameters);
    void onError(QString& err);
signals:
    /*!
    *  \brief [SIGNAL] Emitted each time an error occurs with the data source.
    */
    void error(QString&);


};

#endif // DATASOURCE_H
