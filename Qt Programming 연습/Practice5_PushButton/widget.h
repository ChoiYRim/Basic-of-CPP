#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFocusFrame>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QPushButton *btn[4];
    QFocusFrame *frame;

private slots:
    void btn_click();

    void btn_pressed();

    void btn_released();

};
#endif // WIDGET_H
