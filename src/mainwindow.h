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


    Graph *m_accelerations;
    Graph *m_angles;
    Graph *m_positions;
    Graph *m_pressure;

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
