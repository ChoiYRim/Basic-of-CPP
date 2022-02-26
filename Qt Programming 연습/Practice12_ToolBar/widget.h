#ifndef WIDGET_H
#define WIDGET_H

#include <QToolBar>
#include <QAction>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    virtual ~Widget();

private:
    QToolBar* toolbar;
    QAction*  act[8];

private slots:
    void trigger1();
    void trigger2();
    void trigger3();
    void trigger4();
    void trigger5();
};
#endif // WIDGET_H
