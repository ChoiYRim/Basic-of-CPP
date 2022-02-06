#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(QSize(200,150));

    cmdLinkBtn = new QCommandLinkButton("이동","이 버튼을 누르면 이동합니다.",this);
    //cmdLinkBtn->setFlat(true);
    connect(cmdLinkBtn,SIGNAL(clicked()),this,SLOT(clickedFunc()));
}

void Widget::clickedFunc()
{
    qDebug("이동 버튼이 눌렸습니다.\n");
}

Widget::~Widget()
{
    if(cmdLinkBtn != nullptr)
    {
        delete cmdLinkBtn;
        qDebug("QCommandLinkButton is deleted...\n");
    }
}

