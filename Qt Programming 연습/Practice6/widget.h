#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFontComboBox>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    virtual ~Widget();

private:
    QLabel* label;
    QFontComboBox* fontCombo[8];

private slots:
    void changedIndex(int idx);
    void changedFont(const QFont &f);
};
#endif // WIDGET_H
