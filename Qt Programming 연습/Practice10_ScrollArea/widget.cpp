#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QImage image;

    label = new QLabel(this);
    image = QImage(":resources/fish.png");
    label->setPixmap(QPixmap::fromImage(image));

    area = new QScrollArea(this);
    area->setWidget(label);
    area->setBackgroundRole(QPalette::Dark);
    area->setGeometry(0, 0, image.width(), image.height());
}

Widget::~Widget()
{
    if(label != nullptr)
        delete label;
    if(area != nullptr)
        delete area;
}

