#ifndef WIDGET_H
#define WIDGET_H

#include <QLineEdit>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    virtual ~Widget();

private:
    QLabel* label;
    QLineEdit *edit[8];

private slots:
    void textChanged(QString str);
};
#endif // WIDGET_H
