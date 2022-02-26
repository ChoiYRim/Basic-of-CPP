#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("QScrollBar");
    setFixedSize(QSize(600,300));

    int xpos = 590;

    vScrollBar = new QScrollBar(Qt::Vertical,this);
    vScrollBar->setGeometry(xpos,0,10,280);
    label = new QLabel(QString("%1").arg(vScrollBar->value()),this);
    label->setGeometry(xpos,290,10,10);
    connect(vScrollBar,SIGNAL(valueChanged(int)),this,SLOT(valueChangedSlot(int)));
}

void Widget::valueChangedSlot(int value)
{
    qDebug() << "Value Changed Slot...!\n";
    label->setText(QString("%1").arg(value));
}

Widget::~Widget()
{
    if(label != nullptr)
        delete label;
    if(vScrollBar != nullptr)
        delete vScrollBar;
}

