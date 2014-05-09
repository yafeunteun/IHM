#ifndef ACQUISITIONSETTINGS_H
#define ACQUISITIONSETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QVector>
#include <QVariant>
#include <QComboBox>
#include <map>
#include "qextserialport.h"

using std::map;

class AcquisitionSettings : public QDialog
{
    Q_OBJECT
public:
    typedef enum{SERVER, SERIAL_PORT}Type_t;
    explicit AcquisitionSettings(QWidget *parent = 0);
private:
    void fillVector();
    void makeConnexions();
    QPushButton* m_ok;
    QPushButton* m_cancel;
    QGroupBox* m_server;
    QGroupBox* m_serial;
    QVector<QVariant> m_settings;

    /* Server */
    QLineEdit *m_address;
    QSpinBox *m_port;

    /* Serial port */
    void initMap(void);
    map<QString, BaudRateType> map_baud;
    map<QString, DataBitsType> map_dataBits;
    map<QString, FlowType> map_flowControl;
    map<QString, ParityType> map_parity;
    map<QString, StopBitsType> map_stopBits;

    QComboBox *box_baud;
    QComboBox *box_dataBits;
    QComboBox *box_flowControl;
    QComboBox *box_parity;
    QComboBox *box_stopBit;
    QLineEdit *m_name;


signals:
    void newConfiguration(AcquisitionSettings::Type_t type, const QVector<QVariant>& parameters);/*emitted in onNewConfiguration()*/

public slots:
    void onNewConfiguration(); /* Connected to Ok button */
    void onCancel();            /* Connected to Cancel button */
    void onNewSelection(bool status);      /* Disallow to select both the server and the serial port */


};

#endif // ACQUISITIONSETTINGS_H
