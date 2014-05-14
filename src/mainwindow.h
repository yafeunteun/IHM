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


    Graph *m_accelerations;
    Graph *m_angles;
    Graph *m_positions;
    Graph *m_pressure;

    double temps=0;



private:
    QWidget *parent;
    Ui::MainWindow *ui;
    //ClientTcp *client;

    QAction* m_configureSource;
    QAction* m_startAcquisition;
    QAction* m_stopAcquisition;

    QAction* m_about;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenu();
    void createActions(void);
    double doubleintegration(double acc);
    double filtrerecursif(double);
    void dessindonnees(QVector<double> entree);
    void resetCurves();



private slots :
    void offset();
    void onNewData(QString&);
    void selectSource(void);
    void onError(QString &err);
    void about(void);
};

#endif // MAINWINDOW_H
