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

    Graph *m_accelerations;
    Graph *m_angles;
    Graph *m_positions;
    Graph *m_pressure;

private:
    QWidget *parent;
    Ui::MainWindow *ui;

    /* File */
    QAction* m_saveRecordedData;
    QAction* m_loadRecordedData;
    QAction* m_saveConfiguration;
    QAction* m_loadSensorData;
    QAction* m_quit;

    /* View */
    QAction* m_eraseCurve;

    /* Study */
    QAction* m_startRecord;
    QAction* m_stopRecord;
    QAction* m_drawSpeed;
    QAction* m_drawPosition;

    /* Configuration */
    QAction* m_selectSource;
    QAction* m_calibrateAccelerometer;
    QAction* m_calibrateGyrometer;
    QAction* m_calibrateCurve;

    /* Help */
    QAction* m_manual;
    QAction* m_about;




public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenu();
    void createActions();
    void createStatusBar();
    void createToolBar();
    double doubleintegration(double acc);
    double filtrerecursif(double);
    void dessindonnees(QVector<double> entree);
    void resetCurves();



private slots :
    void onNewData(QString&);
    void selectSource(void);
    void onError(QString &err);
    void about(void);
};

#endif // MAINWINDOW_H
