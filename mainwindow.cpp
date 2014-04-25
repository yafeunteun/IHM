#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <sstream>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_textlabel.h>
#include <qwt_plot_rescaler.h>
#include <qwt_legend.h>
#include "mainwindow.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), parent(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWoffset = new QMainWindow;
    QOffset = new QWidget();

    QWoffset->setWindowTitle("Offsets");
    QWoffset->setCentralWidget(QOffset);

    addMenu();

    ui->ipAdress->setInputMask("000.000.000.000");

    //client = new ClientTcp();

    createCurve();

    addLayout();
    addOffset();
    addGroupBox();
    addCheckBox();
    addPlot();
    addCurve();
    addGrid();
    addMarker();

    //QObject::connect(ui->bConnect, SIGNAL(clicked()), this, SLOT(testip()));
    //QObject::connect(ui->ipAdress, SIGNAL(returnPressed()), this, SLOT(testip()));
    //QObject::connect(client, SIGNAL(vers_IHM_connexion_OK()), this, SLOT(affichage_connexion_ok()));
    //QObject::connect(client, SIGNAL(vers_IHM_connexion_NOTOK()), this, SLOT(affichage_connexion_notok()));
    //** @deprecated **/ QObject::connect(client, SIGNAL(vers_IHM_texte(QString)),this, SLOT(transformation(QString)));
    /** @new **/ QObject::connect(Server::getInstance(), SIGNAL(ReceiveFromPeer(QString)), this, SLOT(transformation(QString)));
    QObject::connect(ui->bPlay, SIGNAL(clicked()),this,SLOT(slotbPlay()));
    QObject::connect(ui->bPause, SIGNAL(clicked()),this,SLOT(slotbPause()));
    QObject::connect(ui->bStop, SIGNAL(clicked()),this,SLOT(slotbStop()));
    QObject::connect(actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrir()));
    QObject::connect(ui->lireFic,SIGNAL(clicked()),this,SLOT(lireFichier()));
    QObject::connect(actionOffset,SIGNAL(triggered()),this,SLOT(offset()));
    QObject::connect(actionSauver,SIGNAL(triggered()),this,SLOT(sauver()));
}

void MainWindow::slotbPlay()
{
     //QObject::connect(client, SIGNAL(vers_IHM_texte(QString)),this, SLOT(transformation(QString)));
     //Case After bpause and bstop
     //client->bPlayPressed();
}


void MainWindow::slotbPause()
{
    //QObject::disconnect(client, SIGNAL(vers_IHM_texte(QString)),this, SLOT(transformation(QString)));

}

void MainWindow::slotbStop()
{
    //QObject::disconnect(client, SIGNAL(vers_IHM_texte(QString)),this, SLOT(transformation(QString)));
    resetCurves();
    temps = 0;
}

void MainWindow::ouvrir()
{
    fichier = QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString());
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
}

void MainWindow::lireFichier()
{
    QFile file(fichier);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&file);
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        ui->textBrowser->append(ligne);
        transformation(ligne);
    }
}

void MainWindow::offset()
{
    if (QWoffset->isVisible())
        QWoffset->hide();
    else
        QWoffset->show();
}

void MainWindow::sauver()
{
    fichierSave = QFileDialog::getSaveFileName(this,"Sauvegarder","./curveSave.txt");
    QMessageBox::information(this, "Fichier", "Courbes sauvegardées dans :\n" + fichierSave);
    QFile file(fichierSave);
    file.open(QIODevice::WriteOnly);
    curveGyroX->saveCurve(file);
    file.close();
}



void MainWindow::affichage_connexion_ok()
{
    ui->stateConn->setText(QString("Connexion OK"));
}

void MainWindow::affichage_connexion_notok()
{
    ui->stateConn->setText(QString("Probleme de connexion"));
}

void MainWindow::testip()
{
    QStringList blocs = ui->ipAdress->text().split(".");
    foreach(QString bloc, blocs)
        if(bloc.toInt() > 255)
        {
            QMessageBox::critical (this, "Validation", ui->ipAdress->text() + " n'est pas valide !");
            ui->ipAdress->clear();
            return;
        }

    sendDatatoClientTcp();
}

void MainWindow::sendDatatoClientTcp()
{
    //client->recoit_IP(ui->ipAdress->text());
}

MainWindow::~MainWindow()
{
    for(CurvePerso *c : curveList)
    {
        delete c;
    }

    delete QWoffset;
    delete ui;
}

void MainWindow::addMenu()
{
    menuFichier = menuBar()->addMenu("Fichier");
    menuOptions = menuBar()->addMenu("Option");

    actionOuvrir = menuFichier->addAction("Ouvrir");
    actionOffset = menuOptions->addAction("Offset");
    actionSauver = menuFichier->addAction("Sauvegarder");
}

void MainWindow::createCurve()
{
    curveGyroX = new CurvePerso("Gyroscope X",QColor(255,0,0),"X",-10);
    curveList.push_back(curveGyroX);
    curveGyroY = new CurvePerso("Gyroscope Y",QColor(128,0,0),"Y",-11);
    curveList.push_back(curveGyroY);
    curveGyroZ = new CurvePerso("Gyroscope Z",QColor(0,255,0),"Z",-12);
    curveList.push_back(curveGyroZ);
    curveAccelX = new CurvePerso("Accéléromètre X",QColor(0,128,128),"X",20);
    curveList.push_back(curveAccelX);
    curveAccelY = new CurvePerso("Accéléromètre Y",QColor(255,0,255),"Y",21);
    curveList.push_back(curveAccelY);
    curveAccelZ = new CurvePerso("Accéléromètre Z",QColor(255,128,0),"Z",22);
    curveList.push_back(curveAccelZ);
    curveMagnetX = new CurvePerso("Magnétomètre X",QColor(128,128,0),"X",-20);
    curveList.push_back(curveMagnetX);
    curveMagnetY = new CurvePerso("Magnétomètre Y",QColor(64,128,128),"Y",-21);
    curveList.push_back(curveMagnetY);
    curveMagnetZ = new CurvePerso("Magnétomètre Z",QColor(128,0,128),"Z",-22);
    curveList.push_back(curveMagnetZ);
    curveTempMPU = new CurvePerso("Température MPU",QColor(64,64,64),"MPU",30);
    curveList.push_back(curveTempMPU);
    curveTempBMP = new CurvePerso("Température BMP",Qt::black,"BMP",31);
    curveList.push_back(curveTempBMP);
    curvePressure = new CurvePerso("Pression",QColor(0,255,255),"Press",32);
    curveList.push_back(curvePressure);
}

void MainWindow::addLayout()
{
    layoutGlobal = new QHBoxLayout(ui->tabAccel);
    layoutControl = new QVBoxLayout;
    layoutCurve = new QVBoxLayout;
    layoutOffset = new QVBoxLayout;

    QOffset->setLayout(layoutOffset);

    layoutGlobal->addLayout(layoutCurve);
    layoutGlobal->addLayout(layoutControl);

    /*Debug*/
    layoutTotal = new QHBoxLayout(ui->tabDebug);
    layoutCurveTotal = new QVBoxLayout;
    layoutControlTotal = new QVBoxLayout;

    layoutTotal->addLayout(layoutCurveTotal);
    layoutTotal->addLayout(layoutControlTotal);
    /*Debug End*/
}

void MainWindow::addOffset()
{
    for(CurvePerso *c : curveList)
    {
        layoutOffset->addLayout(c->getOffsetLayout());
    }
}

void MainWindow::addGroupBox()
{
    vBoxAxes = new QVBoxLayout;
    groupAxes = new QGroupBox("Axes");
    groupAxes->setLayout(vBoxAxes);
    layoutControl->addWidget(groupAxes);

    vBoxOther = new QVBoxLayout;
    groupOther = new QGroupBox("Autres");
    groupOther->setLayout(vBoxOther);
    layoutControl->addWidget(groupOther);

    /*Debug*/
    vBoxGyro = new QVBoxLayout;
    vBoxAccel = new QVBoxLayout;
    vBoxMagnet = new QVBoxLayout;
    vBoxTemp = new QVBoxLayout;
    vBoxPress = new QVBoxLayout;

    groupGyro = new QGroupBox("Gyro");
    groupAccel = new QGroupBox("Accel");
    groupMagnet = new QGroupBox("Magnet");
    groupTemp = new QGroupBox("Temp");
    groupPress = new QGroupBox("Press");

    groupGyro->setLayout(vBoxGyro);
    groupAccel->setLayout(vBoxAccel);
    groupMagnet->setLayout(vBoxMagnet);
    groupTemp->setLayout(vBoxTemp);
    groupPress->setLayout(vBoxPress);

    layoutControlTotal->addWidget(groupGyro);
    layoutControlTotal->addWidget(groupAccel);
    layoutControlTotal->addWidget(groupMagnet);
    layoutControlTotal->addWidget(groupTemp);
    layoutControlTotal->addWidget(groupPress);
    /*Debug End*/
}

void MainWindow::addCheckBox()
{
    axeX = new QCheckBox("Axe X");
    axeX->setChecked(true);
    vBoxAxes->addWidget(axeX);

    axeY = new QCheckBox("Axe Y");
    axeY->setChecked(true);
    vBoxAxes->addWidget(axeY);

    axeZ = new QCheckBox("Axe Z");
    axeZ->setChecked(true);
    vBoxAxes->addWidget(axeZ);

    /*
     *vitesse angulaire
     *position angulaire
     *angle
     *accélération
     *PDF : PS-MPU-9150A
     *Page : 24
     */

    /*Debug*/

    vBoxGyro->addWidget(curveGyroX->getCB());
    vBoxGyro->addWidget(curveGyroY->getCB());
    vBoxGyro->addWidget(curveGyroZ->getCB());

    vBoxAccel->addWidget(curveAccelX->getCB());
    vBoxAccel->addWidget(curveAccelY->getCB());
    vBoxAccel->addWidget(curveAccelZ->getCB());

    vBoxMagnet->addWidget(curveMagnetX->getCB());
    vBoxMagnet->addWidget(curveMagnetY->getCB());
    vBoxMagnet->addWidget(curveMagnetZ->getCB());

    vBoxTemp->addWidget(curveTempMPU->getCB());
    vBoxTemp->addWidget(curveTempBMP->getCB());

    vBoxPress->addWidget(curvePressure->getCB());
    /*Debug End*/
}

void MainWindow::addPlot()
{
    QwtText accel("Accélérations et Vitesses angulaires");
    accel.setFont(QFont(fontInfo().family(), 10));

    plotAccel = new QwtPlot(accel,parent);
    plotAccel->setAxisScale( QwtPlot::xBottom, 0, 10, 1);
    plotAccel->setAxisTitle( QwtPlot::yLeft, "Distance [m]" );
    plotAccel->setAxisScale( QwtPlot::yLeft, 0.0, 20.0 );
    plotAccel->setAxisAutoScale(QwtPlot::xBottom);

    QwtPlotMagnifier *mangn = new QwtPlotMagnifier(plotAccel->canvas());
    mangn->setWheelFactor(1.9);

    zoomAccel = new QwtPlotZoomer(plotAccel->canvas(),true);

    layoutCurve->addWidget(plotAccel);

    QwtLegend *legendAccel = new QwtLegend;
    legendAccel->setFrameStyle(QFrame::Box|QFrame::Sunken);
    plotAccel->insertLegend(legendAccel,QwtPlot::LeftLegend);

    QwtText ang("Vitesses et Angles");
    ang.setFont(QFont(fontInfo().family(), 10));

    plotAng = new QwtPlot(ang,parent);
    plotAng->setAxisScale( QwtPlot::xBottom, 0, 10, 1);
    plotAng->setAxisTitle( QwtPlot::yLeft, "Angle [°]");
    plotAng->setAxisScale( QwtPlot::yLeft, -90.0, 90.0);

    zoomAng = new QwtPlotZoomer(plotAng->canvas(),true);

    layoutCurve->addWidget(plotAng);

    QwtLegend *legendAng = new QwtLegend;
    legendAng->setFrameStyle(QFrame::Box|QFrame::Sunken);
    plotAng->insertLegend(legendAng,QwtPlot::LeftLegend);

    QwtText pos("Positions");
    pos.setFont(QFont(fontInfo().family(), 10));

    plotPos = new QwtPlot(pos,parent);
    plotPos->setAxisTitle( QwtPlot::xBottom, "Temps [s]" );
    plotPos->setAxisScale( QwtPlot::xBottom, 0, 10, 1);
    plotPos->setAxisTitle( QwtPlot::yLeft, "Distance [m]");
    plotPos->setAxisScale( QwtPlot::yLeft, 0.0, 20.0 );

    zoomPos = new QwtPlotZoomer(plotPos->canvas(),true);

    layoutCurve->addWidget(plotPos);

    QwtLegend *legendPos = new QwtLegend;
    legendPos->setFrameStyle(QFrame::Box|QFrame::Sunken);
    plotPos->insertLegend(legendPos,QwtPlot::LeftLegend);

    /*Debug*/
    plotTotal = new QwtPlot(parent);
    plotTotal->setAxisTitle( QwtPlot::xBottom, "Temps [s]" );
    plotTotal->setAxisScale( QwtPlot::xBottom, 0, 10.0, 1);
    plotTotal->setAxisScale( QwtPlot::yLeft, 0.0, 40.0 );
    plotTotal->setAxisAutoScale(QwtPlot::xBottom);
    plotTotal->setAxisAutoScale(QwtPlot::yLeft);

    zoomTotal = new QwtPlotZoomer(plotTotal->canvas(),true);

    magnifierTotal = new QwtPlotMagnifier(plotTotal->canvas());
    magnifierTotal->setWheelFactor(1.9);

    layoutCurveTotal->addWidget(plotTotal);

    QwtLegend *legendTotal = new QwtLegend;
    legendTotal->setFrameStyle(QFrame::Box|QFrame::Sunken);
    plotTotal->insertLegend(legendTotal, QwtPlot::LeftLegend);

    for(CurvePerso *c : curveList)
    {
        c->attachPerso(plotTotal);
    }
    /*Debug End*/
}

/** @todo
 * Constructeur de la classe représentant l'IMU
 * */
void MainWindow::addCurve()
{
    curvePosX = new QwtPlotCurve("Position X");
    curvePosX->setPen(Qt::red);
    curvePosX->attach(plotAccel);
    curvePosY = new QwtPlotCurve("Position Y");
    curvePosY->setPen(Qt::blue);
    curvePosY->attach(plotAccel);
    curvePosZ = new QwtPlotCurve("Position Z");
    curvePosZ->setPen(Qt::black);
    curvePosZ->attach(plotAccel);

    curveRoulis = new QwtPlotCurve("Roulis");
    curveRoulis->attach(plotAng);
    curveTangage = new QwtPlotCurve("Tangage");
    curveTangage->attach(plotAng);
    curveLacet = new QwtPlotCurve("Lacet");
    curveLacet->attach(plotAng);

}


/** @todo
 * L'intérêt est discutable, à voir avec M.Kauffman
 * */
void MainWindow::addGrid()
{
    gridAng = new QwtPlotGrid();
    gridAng->setPen( Qt::black, 0.0, Qt::DotLine );
    gridAng->enableX( true );
    gridAng->enableXMin( true );
    gridAng->enableY( true );
    gridAng->enableYMin( true );
    gridAng->attach(plotAng);

    gridAccel = new QwtPlotGrid();
    gridAccel->setPen( Qt::black, 0.0, Qt::DotLine );
    gridAccel->enableX( true );
    gridAccel->enableXMin( true );
    gridAccel->enableY( true );
    gridAccel->enableYMin( true );
    gridAccel->attach(plotAccel);

    /*Debug*/
    gridTotal = new QwtPlotGrid();
    gridTotal->setPen(Qt::black, 0.0, Qt::DotLine);
    gridTotal->enableX(true);
    gridTotal->enableXMin(true);
    gridTotal->enableY(true);
    gridTotal->enableYMin(true);
    gridTotal->attach(plotTotal);
    /*Debug End*/
}


/** @todo
 * à intégrer dans le constructeur de la classe de gestion des courbes
 * Cette classe pourra représenter l'aspect graphique de l'IMU...
 * */

void MainWindow::addMarker()
{
    originAccel = new QwtPlotMarker();
    originAccel->setLineStyle( QwtPlotMarker::Cross );
    originAccel->setValue( 0, 0.0 );
    originAccel->setLinePen( Qt::black, 0.0, Qt::SolidLine );
    originAccel->attach(plotAccel);

    originAng = new QwtPlotMarker();
    originAng->setLineStyle( QwtPlotMarker::Cross );
    originAng->setValue( 0, 0.0 );
    originAng->setLinePen( Qt::black, 0.0, Qt::SolidLine );
    originAng->attach(plotAng);

    /*Debug*/
    originTotal = new QwtPlotMarker();
    originTotal->setLineStyle( QwtPlotMarker::Cross );
    originTotal->setValue( 0, 0.0 );
    originTotal->setLinePen( Qt::black, 0.0, Qt::SolidLine );
    originTotal->attach(plotTotal);
    /*Debug End*/
}

/** @todo
 * Ce n'est pas à la GUI de réaliser le parsing des données !!
 * Il faudra créer une classe parseur avec éventuellement des méthodes statiques
 * à étudier
 * */

void MainWindow::transformation(QString ligne)
{
   /* int i = 0;//iterator
    double test;
    bool ok;

    QVector<double> vectDonnees;
    QStringList values = ligne.split(" ");
    QVector<double> vectAcc;
    QVector<double> vectAng;
    QVector<double> vectPos;
    QVector<double> vectTraite;

    foreach(QString value, values)
    {
        test = value.toDouble(&ok); // eventually check with ok bool
        if(ok)
        {
            i++;
            vectDonnees.push_back(test);
        }
    }

    if (i!=6)
    {
        vectDonnees.clear();
        return;
    }

    for (i=0;i<3;i++){
        vectAcc.push_back(vectDonnees.at(i));
        vectAng.push_back(vectDonnees.at(i+3));
    }

    for (i=0;i<3;i++){
        vectPos.push_back(doubleintegration(vectAcc.at(i)));
    }

    for (i=0;i<3;i++){
        vectTraite.push_back(vectPos.at(i));
    }

    for (i=0;i<3;i++){
        vectTraite.push_back(vectAng.at(i));
    }*/

    /*Debug*/
    double test;
    bool ok;
    QStringList values = ligne.split(" ");
    QVector<double> vectDonnees;

    foreach(QString value, values)
    {
        test = value.toDouble(&ok); // eventually check with ok bool
        if(ok)
        {
            vectDonnees.push_back(test);
        }
    }
    /*Debug End*/

    if(vectDonnees.size() != 12){
        return;
    }else{
       //dessindonnees(vectTraite);
       dessindonnees(vectDonnees);
    }
}

/** @todo
 * Passer un QVector en argument ralentit le programme
 * il vaut mieux passer une référence ou un pointeur
 * De toutes façon il faudra centraliser les données dans une classe DataHolder
 * qui sera un singleton */
void MainWindow::dessindonnees(QVector<double> entree){
    vectTemps.push_back(temps);
    /*posx.push_back(entree.at(0));
    posy.push_back(entree.at(1));
    posz.push_back(entree.at(2));
    roulis.push_back(entree.at(3));
    tangage.push_back(entree.at(4));
    lacet.push_back(entree.at(5));


    curvePosX->setSamples(vectTemps,posx);
    curvePosY->setSamples(vectTemps,posy);
    curvePosZ->setSamples(vectTemps,posz);
    curveRoulis->setSamples(vectTemps,roulis);
    curveTangage->setSamples(vectTemps,tangage);
    curveLacet->setSamples(vectTemps,lacet);*/

    /*Debug*/
    //Gx.push_back(entree.at(0)+gyroOffset);
    curveGyroX->addData(entree.at(0));
    curveGyroY->addData(entree.at(1));
    curveGyroZ->addData(entree.at(2));
    curveAccelX->addData(entree.at(3));
    curveAccelY->addData(entree.at(4));
    curveAccelZ->addData(entree.at(5));
    curveMagnetX->addData(entree.at(6));
    curveMagnetY->addData(entree.at(7));
    curveMagnetZ->addData(entree.at(8));
    curveTempMPU->addData(entree.at(9));
    curvePressure->addData(entree.at(10));
    curveTempBMP->addData(entree.at(11));

    for(CurvePerso *c : curveList)
    {
        c->setSamplesPerso(vectTemps);
    }
    /*Debug End*/

    temps += 0.01;


    //plotAccel->replot();
    //plotAng->replot();

    plotTotal->replot();
}


/** @todo
 * Méthode à intégrer dans la classe gérant les graphiques */
void MainWindow::resetCurves()
{
    vectTemps.clear();

    posx.clear();
    posy.clear();
    posz.clear();
    roulis.clear();
    tangage.clear();
    lacet.clear();

    /*Debug*/

    curveGyroX->clearData();
    curveGyroY->clearData();
    curveGyroZ->clearData();
    curveAccelX->clearData();
    curveAccelY->clearData();
    curveAccelZ->clearData();
    curveMagnetX->clearData();
    curveMagnetY->clearData();
    curveMagnetZ->clearData();
    curveTempMPU->clearData();
    curvePressure->clearData();
    curveTempBMP->clearData();

    /*Debug End*/
}

/** @todo
 * Ajouter cette méthode dans une classe Maths
 * méthode statique*/
double MainWindow::doubleintegration(double acc){
    double vitesse;
    double position;

    vitesse=acc*1.01;
    //a=d/t
    position=vitesse*1.01;
    //v=d/t
    return position;
}
