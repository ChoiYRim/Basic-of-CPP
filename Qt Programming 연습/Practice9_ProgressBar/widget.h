#ifndef WIDGET_H
#define WIDGET_H

#include <QProgressBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    virtual ~Widget();

private:
    QProgressBar* progress;
    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* resetButton;
    QTimer* timer;
    QHBoxLayout* layout;
    qint64 cur;

private slots:
    void start();
    void reset();
    void stop();
    void update();
};
#endif // WIDGET_H
