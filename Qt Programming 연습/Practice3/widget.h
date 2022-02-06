#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCommandLinkButton>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QCommandLinkButton* cmdLinkBtn;

private slots:
    void clickedFunc();
};
#endif // WIDGET_H
