#include "curveperso.h"
#include <sstream>
#include <QMessageBox>
#include <QTextCodec>

CurvePerso::CurvePerso(QString name, QColor color, QString nameCB, int offset)
    :offset(offset)
{
    curve = new QwtPlotCurve(name);
    curve->setPen(color);

    CB = new QCheckBox(nameCB);
    CB->setChecked(true);

    QPalette pal;
    pal.setColor(QPalette::WindowText,color);
    offsetLabel = new QLabel(name);
    offsetLabel->setPalette(pal);

    offsetSpin = new QSpinBox;
    offsetSpin->setRange(-100,1000);
    offsetSpin->setValue(offset);

    layoutOffset = new QHBoxLayout;
    layoutOffset->addWidget(offsetLabel);
    layoutOffset->addWidget(offsetSpin);

    QObject::connect(CB,SIGNAL(stateChanged(int)),this,SLOT(setVisibleCurve(int)));
    QObject::connect(offsetSpin,SIGNAL(valueChanged(int)),this,SLOT(setOffset(int)));

    saveFile = new QFile(name.replace(" ","")+".bak");
    saveFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream streamFile(saveFile);
    streamFile.setCodec(QTextCodec::codecForName("UTF-8"));
    streamFile << "Courbe : " << name.toStdString().c_str() << "\n";
    streamFile << "_BeginData_\n";
}

CurvePerso::~CurvePerso()
{
    QTextStream streamFile(saveFile);
    streamFile << "_EndData_\n";
    saveFile->close();

    delete saveFile;
    delete offsetLabel;
    delete offsetSpin;
    delete layoutOffset;
    delete CB;
    delete curve;
}

QCheckBox *CurvePerso::getCB()
{
    return CB;
}

void CurvePerso::attachPerso(QwtPlot *plot)
{
    this->plot = plot;
    curve->attach(this->plot);
}

void CurvePerso::setSamplesPerso(QVector<double> tmp)
{
    curve->setSamples(tmp, data);
}

void CurvePerso::addData(double point)
{
    QTextStream streamFile(saveFile);
    streamFile << point << "\n";
    data.push_back(point+offset);
}

void CurvePerso::clearData()
{
    data.clear();
}

void CurvePerso::saveCurve(QFile &file)
{
    for(double i : data)
    {
        std::stringstream ss;
        ss << i;
        file.write(ss.str().c_str());
    }
}

QHBoxLayout *CurvePerso::getOffsetLayout()
{
    return layoutOffset;
}

void CurvePerso::setVisibleCurve(int state)
{
    if (state == 0)
        curve->setVisible(false);
    if (state == 2)
        curve->setVisible(true);
    plot->replot();
}

void CurvePerso::setOffset(int value)
{
    offset = value;
}
