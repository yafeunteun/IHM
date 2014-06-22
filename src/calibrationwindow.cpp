#include "calibrationwindow.h"
#include "imu.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>


/*!
    *  \brief Constructor
    *
    *  Constructor of AcquisitionSettings class
    *
    *  \param parent : Constructs a widget which is a child of parent.
    */
CalibrationWindow::CalibrationWindow(QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QFont font;
    font.setBold(true);

    QLabel* accLabel = new QLabel("Accelerometers");
    accLabel->setAlignment(Qt::AlignCenter);
    accLabel->setFont(font);

    QLabel* gyrLabel = new QLabel("Gyrometers");
    gyrLabel->setAlignment(Qt::AlignCenter);
    gyrLabel->setFont(font);

    QLabel* magLabel = new QLabel("Magnetometers");
    magLabel->setAlignment(Qt::AlignCenter);
    magLabel->setFont(font);

    QLabel* barTempLabel = new QLabel("Barometer and Temperature sensors");
    barTempLabel->setAlignment(Qt::AlignCenter);
    barTempLabel->setFont(font);

    m_accelerometers = new QTableWidget(3, 5);
    QStringList labelsRows = {"X axis", "Y axis", "Z axis"};
    QStringList labelsCols = {"Measures", "Sensitivity", "Offset", "Temp. sens.", "Temp. offset"};
    m_accelerometers->setVerticalHeaderLabels(labelsRows);
    m_accelerometers->setHorizontalHeaderLabels(labelsCols);

    m_gyrometers = new QTableWidget(3, 5);
    m_gyrometers->setVerticalHeaderLabels(labelsRows);
    m_gyrometers->setHorizontalHeaderLabels(labelsCols);

    m_magnetometers = new QTableWidget(3, 4);
    labelsCols = {"Measures", "Sensitivity", "Offset", "Temp. offset"};
    m_magnetometers->setVerticalHeaderLabels(labelsRows);
    m_magnetometers->setHorizontalHeaderLabels(labelsCols);

    m_barTemp = new QTableWidget(1,4);
    labelsCols = {"Pressure", "Altitude","", "Temperature"};
    m_barTemp->setHorizontalHeaderLabels(labelsCols);

    QTableWidgetItem*  item;
    for(int i = 0; i < m_accelerometers->rowCount(); ++i){
        item = new QTableWidgetItem;
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        item->setBackgroundColor(QColor::fromRgb(225,226,255));
        m_accelerometers->setItem(i,0,item);
    }

    for(int i = 0; i < m_gyrometers->rowCount(); ++i){
        item = new QTableWidgetItem;
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        item->setBackgroundColor(QColor::fromRgb(225,226,255));
        m_gyrometers->setItem(i,0,item);
    }

    for(int i = 0; i < m_magnetometers->rowCount(); ++i){
        item = new QTableWidgetItem;
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        item->setBackgroundColor(QColor::fromRgb(225,226,255));
        m_magnetometers->setItem(i,0,item);
    }

    for(int i = 3; i < m_accelerometers->columnCount(); ++i){
        for(int j = 1; j < m_accelerometers->rowCount(); ++j){
            item = new QTableWidgetItem;
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            item->setBackgroundColor(QColor::fromRgb(255,255,255));
            m_accelerometers->setItem(j,i,item);
        }
    }

    for(int i = 3; i < m_gyrometers->columnCount(); ++i){
        for(int j = 1; j < m_gyrometers->rowCount(); ++j){
            item = new QTableWidgetItem;
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            item->setBackgroundColor(QColor::fromRgb(255,255,255));
            m_gyrometers->setItem(j,i,item);
        }
    }

    for(int i = 3; i < m_magnetometers->columnCount(); ++i){
        for(int j = 1; j < m_magnetometers->rowCount(); ++j){
            item = new QTableWidgetItem;
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            item->setBackgroundColor(QColor::fromRgb(255,255,255));
            m_magnetometers->setItem(j,i,item);
        }
    }

    m_barTemp->setItem(0, 0, new QTableWidgetItem());
    m_barTemp->setItem(0, 2, new QTableWidgetItem());
    m_barTemp->setItem(0, 3, new QTableWidgetItem());
    m_barTemp->item(0,0)->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    m_barTemp->item(0,0)->setBackgroundColor(QColor::fromRgb(225,226,255));
    m_barTemp->item(0,2)->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    m_barTemp->item(0,3)->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    m_barTemp->item(0,3)->setBackgroundColor(QColor::fromRgb(225,226,255));

    mainLayout->addWidget(accLabel);
    mainLayout->addWidget(m_accelerometers);
    mainLayout->addWidget(gyrLabel);
    mainLayout->addWidget(m_gyrometers);
    mainLayout->addWidget(magLabel);
    mainLayout->addWidget(m_magnetometers);
    mainLayout->addWidget(barTempLabel);
    mainLayout->addWidget(m_barTemp);
    this->setLayout(mainLayout);
    this->setFixedWidth(m_accelerometers->columnWidth(0)*6);


}


/*!
    *  \brief Performed each time new data has been calibrated.
    *
    *  Update every label with the new value received. There is a label for each sensor.
    *
    *  \param data : A vector containing the new calibrated data.
    */
void CalibrationWindow::onNewCalibratedData(std::vector<float>& data)
{

}
