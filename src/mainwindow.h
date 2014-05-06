#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "ui_IHM.h"
#include "graph.h"

namespace Ui {
class MainWindow;
}

class CurvePerso;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /** @todo
    //void createActions(void);
    //void createMenus(void);
    //void createStatusBar(void);
    //void createToolBar(void);
    **/

    QMainWindow *QWoffset;
    QWidget *QOffset;

    QMenu *menuFichier;
    QMenu *menuOptions;
    QAction *actionOffset;

    //QHBoxLayout *layoutGlobal;
    //QVBoxLayout *layoutControl;
    //QVBoxLayout *layoutCurve;
    //QVBoxLayout *layoutOffset;

    //QGroupBox *groupAxes;
    //QGroupBox *groupOther;

    //QVBoxLayout *vBoxAxes;
    //QVBoxLayout *vBoxOther;

    //QCheckBox *axeX;
    //QCheckBox *axeY;
    //QCheckBox *axeZ;
    //QCheckBox *accel;
    //QCheckBox *vitAng;
    //QCheckBox *vitesse;
    //QCheckBox *ang;

    //QwtPlot *plotAccel;
    //QwtPlot *plotAng;
    //QwtPlot *plotPos;

    Graph *m_accelerations;
    Graph *m_angles;
    Graph *m_positions;

    //QwtPlotZoomer *zoomAccel;
    //QwtPlotZoomer *zoomAng;
    //QwtPlotZoomer *zoomPos;

    //QwtPlotCurve *curvePosX;
    //QwtPlotCurve *curvePosY;
    //QwtPlotCurve *curvePosZ;
    //QwtPlotCurve *curveRoulis;
    //QwtPlotCurve *curveTangage;
    //QwtPlotCurve *curveLacet;

    //QwtPlotGrid *gridAccel;
    //QwtPlotGrid *gridAng;
    //QwtPlotGrid *gridPos;

    //QwtPlotMarker *originAccel;
    //QwtPlotMarker *originAng;
    //QwtPlotMarker *originPos;

    /*Debug atributes*/

    //QHBoxLayout *layoutTotal;
    //QVBoxLayout *layoutCurveTotal;
    //QVBoxLayout *layoutControlTotal;

    //QGroupBox *groupGyro;
    //QGroupBox *groupAccel;
    //QGroupBox *groupMagnet;
    //QGroupBox *groupTemp;
    //QGroupBox *groupPress;

    //QVBoxLayout *vBoxGyro;
    //QVBoxLayout *vBoxAccel;
    //QVBoxLayout *vBoxMagnet;
    //QVBoxLayout *vBoxTemp;
    //QVBoxLayout *vBoxPress;

    //QwtPlot *plotTotal;
    //QwtPlotZoomer *zoomTotal;
    //QwtPlotMagnifier *magnifierTotal;

    //QwtPlotGrid *gridTotal;
    //QwtPlotMarker *originTotal;

    //CurvePerso *curveGyroX;
    //CurvePerso *curveGyroY;
    //CurvePerso *curveGyroZ;
    //CurvePerso *curveAccelX;
    //CurvePerso *curveAccelY;
    //CurvePerso *curveAccelZ;
    //CurvePerso *curveMagnetX;
   // CurvePerso *curveMagnetY;
    //CurvePerso *curveMagnetZ;
    //CurvePerso *curveTempMPU;
    //CurvePerso *curvePressure;
    //CurvePerso *curveTempBMP;

    //std::list<CurvePerso*> curveList;

    /*Debug End*/


    double temps=0;



private:
    QWidget *parent;
    Ui::MainWindow *ui;
    //ClientTcp *client;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addMenu();
    void createCurve();
    void addLayout();
    void addOffset();
    void addGroupBox();
    void addCheckBox();
    void addPlot();
    void addCurve();
    void addGrid();
    void addMarker();
    void sendDatatoClientTcp();
    double doubleintegration(double acc);
    double filtrerecursif(double);
    void dessindonnees(QVector<double> entree);
    void resetCurves();



private slots :
    void offset();
    void onNewData(QString&);
};

#endif // MAINWINDOW_H
