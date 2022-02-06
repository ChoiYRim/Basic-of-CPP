#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QScrollArea>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QScrollArea* area;
    QLabel* label;
};
#endif // WIDGET_H
