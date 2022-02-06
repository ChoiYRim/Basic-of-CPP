#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("QCombobox");

    combo = new QComboBox(this);
    combo->setGeometry(50,50,200,30);
    combo->addItem(QIcon(":/resources/math.png"),"Math");
    combo->addItem(QIcon(":/resources/english.png"),"English");
    combo->addItem(QIcon(":/resources/science.png"),"Science");
    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(valueChanged()));
}

void Widget::valueChanged()
{
    int index = combo->currentIndex();
    qDebug("Selected index : %d\n", index);
}

Widget::~Widget()
{
    if(combo != nullptr)
    {
        delete combo;
        qDebug("QCombobox object is deleted...\n");
    }
}

