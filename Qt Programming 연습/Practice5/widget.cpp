#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    for(size_t i = 0; i < 4; i++)
        btn[i] = nullptr;

    int ypos = 30;
    setWindowTitle("QPushButton");

    for(size_t i = 0; i < 3; i++)
    {
        btn[i] = new QPushButton(QString("Button ").arg(i+1),this);
        btn[i]->setGeometry(10,ypos,140,30);
        ypos += 50;
    }

    connect(btn[0],&QPushButton::clicked,this,&Widget::btn_click);
    connect(btn[0],&QPushButton::pressed,this,&Widget::btn_pressed);
    connect(btn[0],&QPushButton::released,this,&Widget::btn_released);

    frame = new QFocusFrame(this);
    frame->setWidget(btn[0]);
    //frame->setAutoFillBackground(false);
}

void Widget::btn_click()
{
    qDebug("Button Click");
}

void Widget::btn_pressed()
{
    qDebug("Button Pressed");
}

void Widget::btn_released()
{
    qDebug("Button Relased");
}

Widget::~Widget()
{
    for(size_t i = 0; i < 4; i++)
        if(btn[i] != nullptr)
            delete btn[i];
    if(frame != nullptr)
        delete frame;
}

