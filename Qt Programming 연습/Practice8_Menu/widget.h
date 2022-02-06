#ifndef WIDGET_H
#define WIDGET_H

#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QAction>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QMenuBar* menuBar;
    QMenu* menu[4];
    QAction* act[2];
    QLabel* label;

private slots:
    void trigerMenu(QAction* act);
};
#endif // WIDGET_H
