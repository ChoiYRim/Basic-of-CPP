#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    newAct = new QAction(QIcon(":/images/new.png"),tr("&New"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"),tr("&Open"),this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);

    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);

    dock = new QDockWidget(tr("Target"),this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    customerList = new QListWidget(dock);
    customerList->addItems(QStringList() << "One" << "Two" << "Three" << "Four" << "Five");

    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    setCentralWidget(new MDIMainWindow());
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::newFile()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::open()
{
    qDebug() << Q_FUNC_INFO;
}

MainWindow::~MainWindow()
{
    if(fileMenu != nullptr) delete fileMenu;
    if(newAct != nullptr) delete newAct;
    if(openAct != nullptr) delete openAct;
    if(fileToolBar != nullptr) delete fileToolBar;
    if(dock != nullptr) delete dock ;
    if(customerList != nullptr) delete customerList;
}
