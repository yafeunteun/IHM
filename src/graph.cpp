#include <QGroupBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QColorDialog>
#include <qwt_plot_textlabel.h>

#include "graph.h"



Graph::Graph(std::initializer_list<QString> labels, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    QGroupBox *g1 = new QGroupBox();
    QGroupBox *g2 = new QGroupBox();
    QFormLayout *l1 = new QFormLayout();
    QFormLayout *l2 = new QFormLayout();

    m_plot = new QwtPlot();
    m_plot->setAutoReplot(true);

    m_dataHolder = new DataHolder(labels);

    for(QString label : labels)
    {
        QPushButton *b = new QPushButton();
        QCheckBox *ch = new QCheckBox();
        Curve *cu = new Curve(m_dataHolder->getDataSet(label), QColor::colorNames()[m_colorIndex++]);
        b->setFixedSize(20,20);
        ch->setFixedSize(20,20);
        m_buttons.append(b);
        m_checkboxes.append(ch);
        m_curves.append(cu);

        l1->addRow(label, b);
        l2->addRow(label, ch);
    }

    m_colorIndex = 13;

    for(Curve* curve : m_curves)
    {
        curve->attach(m_plot);
    }

    for(QCheckBox* box : m_checkboxes)
    {
        box->setChecked(true);
        QObject::connect(box, SIGNAL(stateChanged(int)), this, SLOT(curveDisplay()));
    }

    for(QPushButton* button : m_buttons)
    {
        QString colName = QColor::colorNames()[m_colorIndex++];
        QString qss = QString("background-color: " + colName);
        button->setStyleSheet(qss);
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(changeColor()));
    }

    g1->setLayout(l1);
    g2->setLayout(l2);

    layout->addWidget(g1);
    layout->addWidget(m_plot);
    layout->addWidget(g2);

    this->setLayout(layout);
    //this->setFixedHeight(200);
}

void Graph::curveDisplay()
{
    int index = m_checkboxes.indexOf((QCheckBox*)QObject::sender());
    m_curves[index]->setVisible(((QCheckBox*)QObject::sender())->isChecked());

}

void Graph::changeColor()
{
    QPushButton* sender = (QPushButton*)QObject::sender();
    int index = m_buttons.indexOf(sender);
    QColor col = QColorDialog::getColor(Qt::white, this);

    if(col.isValid()) {
        QString qss = QString("background-color: %1").arg(col.name());
        sender->setStyleSheet(qss);
        m_curves[index]->setColor(col);
    }
}

void Graph::setTitle(const QString& title)
{
    m_plot->setTitle(title);
}
