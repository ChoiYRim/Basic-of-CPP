#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QDate date1 = QDate(2022,1,1);
    QDate date2 = QDate::currentDate();
    QString str = date2.toString("yy.M.dd");

    dateEdits.emplace_back(new QDateEdit(date1.addYears(2),this));
    dateEdits.back()->setGeometry(10,10,140,40);

    dateEdits.emplace_back(new QDateEdit(date1.addMonths(3),this));
    dateEdits.back()->setGeometry(160,10,140,40);

    dateEdits.emplace_back(new QDateEdit(date1.addDays(10),this));
    dateEdits.back()->setGeometry(310,10,140,40);

    dateEdits.emplace_back(new QDateEdit(date2,this));
    dateEdits.back()->setGeometry(460,10,140,40);

    const int width = this->width();
    //qDebug() << str << '\n';
    label = new QLabel(str,this);
    label->setGeometry(width/2-70,50,140,40);
}

Widget::~Widget()
{
    if(label != nullptr)
        delete label;
    while(!dateEdits.empty())
    {
        auto& cur = dateEdits.back();
        dateEdits.pop_back();
        delete cur;
    }
}

