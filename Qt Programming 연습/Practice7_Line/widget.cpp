#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("QLineEdit Test");

    int ypos = 120;
    label = nullptr;
    for(size_t i = 0; i < 8; i++) edit[i] = nullptr;

    edit[0] = new QLineEdit("",this);
    label = new QLabel("QLineEdit Text : ", this);
    connect(edit[0],SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));

    edit[0]->setGeometry(10,30,200,40);
    label->setGeometry(10,80,250,30);
    for(size_t i = 1; i < 5; i++)
    {
        edit[i] = new QLineEdit("test test.",this);
        edit[i]->setGeometry(10,ypos,200,40);
        ypos += 50;
    }
    edit[1]->setEchoMode(QLineEdit::Normal); // 디폴트
    edit[2]->setEchoMode(QLineEdit::NoEcho); // 텍스트가 안보이며 커서의 위치도 안보임
    edit[3]->setEchoMode(QLineEdit::Password); // 텍스트가 *로 표시됨
    edit[4]->setEchoMode(QLineEdit::PasswordEchoOnEdit); // 텍스트가 변경되면 디폴트와 동일하지만 포커스가 이동하면 *로 표시됨
}

void Widget::textChanged(QString str)
{
    label->setText(QString("QLineEdit Text : %1").arg(str));
}

Widget::~Widget()
{
    for(size_t i = 0; i < 8; i++)
        if(edit[i] != nullptr)
            delete edit[i];
    delete label;
}

