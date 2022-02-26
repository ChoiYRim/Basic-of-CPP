#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
#include <QStatusBar>
#include <QDebug>
#include "mdimainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

private:
    QMenu* fileMenu = nullptr;
    QAction* newAct = nullptr;
    QAction* openAct = nullptr;
    QToolBar* fileToolBar = nullptr;

    QDockWidget* dock = nullptr;
    QListWidget* customerList = nullptr;

private slots:
    void newFile();
    void open();
};

#endif // MAINWINDOW_H
