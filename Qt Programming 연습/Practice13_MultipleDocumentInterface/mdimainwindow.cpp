#include "mdimainwindow.h"

MDIMainWindow::MDIMainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString::fromUtf8("My MDI"));

    area = new QMdiArea();
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    subWindow1 = new QMdiSubWindow();
    subWindow1->resize(300, 200);

    btn = new QPushButton(QString("Button"));
    subWindow1->setWidget(btn);

    subWindow2 = new QMdiSubWindow();
    subWindow2->resize(300, 200);

    area->addSubWindow(subWindow1);
    area->addSubWindow(subWindow2);
    setCentralWidget(area);
}

MDIMainWindow::~MDIMainWindow()
{
    if(btn != nullptr) delete btn;
    if(subWindow1 != nullptr) delete subWindow1;
    if(subWindow2 != nullptr) delete subWindow2;
    if(area != nullptr) delete area;
}

