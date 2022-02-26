#ifndef WIDGET_H
#define WIDGET_H

#include <QAbstractSlider>
#include <QScrollBar>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QLabel*     label;
    QScrollBar* vScrollBar;

private slots:
    void valueChangedSlot(int value);
};
#endif // WIDGET_H
