#ifndef MDIMAINWINDOW_H
#define MDIMAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>

class MDIMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MDIMainWindow(QWidget *parent = nullptr);
    virtual ~MDIMainWindow();

private:
    QMdiArea* area = nullptr;
    QMdiSubWindow* subWindow1 = nullptr;
    QPushButton* btn = nullptr;
    QMdiSubWindow* subWindow2 = nullptr;
};
#endif // MDIMAINWINDOW_H
