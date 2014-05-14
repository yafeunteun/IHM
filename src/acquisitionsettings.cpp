#include "acquisitionsettings.h"
#include "acquisitionsettingsproxy.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

AcquisitionSettings::AcquisitionSettings(QWidget *parent) :
    QDialog(parent)
{
    this->setModal(true);
    this->setFixedSize(this->minimumSize());

    m_ok = new QPushButton("Ok");
    m_cancel = new QPushButton("Cancel");
    m_address = new QLineEdit();
    m_port = new QSpinBox();


    m_server = new QGroupBox();
    QFormLayout* serverLayout = new QFormLayout();
    serverLayout->addRow("Address", m_address);
    serverLayout->addRow("Port", m_port);
    m_port->setMinimum(1025);
    m_port->setMaximum(65535);
    m_port->setValue(20000);
    m_address->setText("192.168.1.2");
    m_address->setReadOnly(true);
    m_address->setEnabled(false);
    m_server->setTitle("&Server");
    m_server->setCheckable(true);
    m_server->setChecked(true);
    m_server->setLayout(serverLayout);


    /*SERIAL PORT */

    m_serial = new QGroupBox();
    QFormLayout* serialLayout = new QFormLayout();
    initMap();

    box_port = new QComboBox;
    box_port->addItem("COM1");
    box_port->addItem("COM2");
    box_port->addItem("COM3");
    box_port->addItem("COM4");
    box_port->addItem("COM5");
    box_port->addItem("COM6");
    box_port->addItem("COM7");
    box_port->addItem("COM8");
    box_port->addItem("COM9");

    box_baud = new QComboBox;
    box_baud->addItem("BAUD9600");
    box_baud->addItem("BAUD19200");
    box_baud->addItem("BAUD115200");
    box_baud->setCurrentText("BAUD115200");

    box_dataBits = new QComboBox;
    box_dataBits->addItem("DATA_8");
    box_dataBits->addItem("DATA_7");
    box_dataBits->addItem("DATA_6");
    box_dataBits->addItem("DATA_5");

    box_flowControl = new QComboBox();
    box_flowControl->addItem("FLOW_OFF");           // No flow control
    box_flowControl->addItem("FLOW_HARDWARE");      // Hardware (RTS/CTS) flow control
    box_flowControl->addItem("FLOW_XONXOFF");       // Software (XON/XOFF) flow control

    box_parity = new QComboBox();
    box_parity->addItem("PAR_NONE");
    box_parity->addItem("PAR_SPACE");
    box_parity->addItem("PAR_EVEN");
    box_parity->addItem("PAR_ODD");

    box_stopBit = new QComboBox();
    box_stopBit->addItem("STOP_1");
    box_stopBit->addItem("STOP_2");


    serialLayout->addRow("Port name : ", box_port);
    serialLayout->addRow("Baud rate", box_baud);
    serialLayout->addRow("Number of data bits", box_dataBits);
    serialLayout->addRow("Flow control", box_flowControl);
    serialLayout->addRow("Parity", box_parity);
    serialLayout->addRow("Number of stop bits", box_stopBit);
    m_serial->setTitle("Serial &Port");
    m_serial->setCheckable(true);
    m_serial->setChecked(false);
    m_serial->setLayout(serialLayout);


    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(m_ok);
    buttons->addWidget(m_cancel);


    QVBoxLayout *global = new QVBoxLayout();
    global->addWidget(m_server);
    global->addWidget(m_serial);
    global->addLayout(buttons);

    this->setLayout(global);
    this->makeConnexions();

}

void AcquisitionSettings::initMap()
{
    map_port["COM1"] = "COM1";
    map_port["COM2"] = "COM2";
    map_port["COM3"] = "COM3";
    map_port["COM4"] = "COM4";
    map_port["COM5"] = "COM5";
    map_port["COM6"] = "COM6";
    map_port["COM7"] = "COM7";
    map_port["COM8"] = "COM8";
    map_port["COM9"] = "COM9";

    map_baud["BAUD9600"] = BAUD9600;
    map_baud["BAUD19200"] = BAUD19200;
    map_baud["BAUD115200"] = BAUD115200;

    map_dataBits["DATA_5"] = DATA_5;
    map_dataBits["DATA_6"] = DATA_6;
    map_dataBits["DATA_7"] = DATA_7;
    map_dataBits["DATA_8"] = DATA_8;

    map_flowControl["FLOW_OFF"] = FLOW_OFF;
    map_flowControl["FLOW_HARDWARE"] = FLOW_HARDWARE;
    map_flowControl["FLOW_XONXOFF"] = FLOW_XONXOFF;

    map_parity["PAR_SPACE"] = PAR_SPACE;
    map_parity["PAR_NONE"] = PAR_NONE;
    map_parity["PAR_EVEN"] = PAR_EVEN;
    map_parity["PAR_ODD"] = PAR_ODD;

    map_stopBits["STOP_1"] = STOP_1;
    map_stopBits["STOP_2"] = STOP_2;
}


void AcquisitionSettings::makeConnexions()
{
    QObject::connect(m_ok, SIGNAL(clicked()), this, SLOT(onNewConfiguration()));
    QObject::connect(m_cancel, SIGNAL(clicked()), this, SLOT(onCancel()));

    QObject::connect(m_serial, SIGNAL(toggled(bool)), this, SLOT(onNewSelection(bool)));
    QObject::connect(m_server, SIGNAL(toggled(bool)), this, SLOT(onNewSelection(bool)));

    QObject::connect(this, SIGNAL(newConfiguration(AcquisitionSettings::Type_t,QVector<QVariant>)), AcquisitionSettingsProxy::getInstance(), SLOT(configure(AcquisitionSettings::Type_t,QVector<QVariant>)));
}

void AcquisitionSettings::onNewConfiguration()
{
    this->fillVector();

    if(m_server->isChecked())
    {
        emit newConfiguration(AcquisitionSettings::SERVER, m_settings);
    }else{
        emit newConfiguration(AcquisitionSettings::SERIAL_PORT, m_settings);
    }
    this->close();
}

void AcquisitionSettings::onCancel()
{
    this->close();
}

/* Fill the vector with current configuration */
void AcquisitionSettings::fillVector()
{
    /* reset m_setings content */
    m_settings.clear();

    if(m_server->isChecked())
    {
        quint16 port = m_port->value();
        QString addr = m_address->text();
        m_settings.append(port);
        m_settings.append(addr);
    }else{
        QString name = map_port.find(box_port->currentText())->second;
        BaudRateType baudRate = map_baud.find(box_baud->currentText())->second;
        DataBitsType dataBits = map_dataBits.find(box_dataBits->currentText())->second;
        FlowType flow = map_flowControl.find(box_flowControl->currentText())->second;
        ParityType parity = map_parity.find(box_parity->currentText())->second;
        StopBitsType stopBits = map_stopBits.find(box_stopBit->currentText())->second;

        m_settings.append(name);
        m_settings.append(baudRate);
        m_settings.append(dataBits);
        m_settings.append(flow);
        m_settings.append(parity);
        m_settings.append(stopBits);
    }
}

void AcquisitionSettings::onNewSelection(bool status)
{
    if(this->sender() == m_serial)
    {
        m_server->setChecked(!status);
    }else{
        m_serial->setChecked(!status);
    }
}
