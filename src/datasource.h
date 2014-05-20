#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include "serialport.h"
#include "server.h"
#include "acquisitionsettings.h"


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
    void error(QString&);


};

#endif // DATASOURCE_H
