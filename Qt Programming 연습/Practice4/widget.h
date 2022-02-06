#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDate>
#include <QDateEdit>
#include <QLabel>
#include <memory>
#include <QVector>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QLabel* label;
    QVector<QDateEdit*> dateEdits;
};
#endif // WIDGET_H
