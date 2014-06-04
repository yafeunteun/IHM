#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file mainwindow.h
 * \author yann feunteun
 * \version 0.1
 * \date 05/14/2014
 */

#include <QMainWindow>
#include <QtGui>
#include "ui_IHM.h"
#include "graph.h"

namespace Ui {
class MainWindow;
}


/*! \class MainWindow
   * \brief This class represents the main window of this software.
   */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    Graph *m_accelerations;
    Graph *m_angles;
    Graph *m_positions;
    Graph *m_pressure;
    Graph *m_temperature;

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
    QAction* m_calibrate;

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


private slots :
    void updateView();
    void selectSource(void);
    void onError(QString &err);
    void onStatusChanged(QString& stat, int timeout);
    void about(void);
    void onSaveRecordedData(void);
    void onCalibrate(void);
};

#endif // MAINWINDOW_H
