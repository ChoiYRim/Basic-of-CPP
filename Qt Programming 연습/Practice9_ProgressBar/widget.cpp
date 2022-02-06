#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), cur(0)
{
    setWindowTitle("QProgressBar Test");
    setFixedSize(500,200);

    progress = new QProgressBar(this);
    progress->setValue(0); // 시작값 0
    progress->setMinimum(0); // min : 0
    progress->setMaximum(100); // max : 100
    progress->setOrientation(Qt::Horizontal);
    progress->setGeometry(10,30,300,30);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    startButton = new QPushButton(QString("Start"));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));

    stopButton = new QPushButton(QString("Stop"));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stop()));

    resetButton = new QPushButton(QString("Reset"));
    connect(resetButton,SIGNAL(clicked()),this,SLOT(reset()));

    layout = new QHBoxLayout;
    layout->addWidget(progress);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);
    layout->addWidget(resetButton);
    setLayout(layout);
}

void Widget::start()
{
    startButton->setEnabled(true);
    timer->start(100);
}

void Widget::reset()
{
    startButton->setEnabled(true);
    timer->stop();
    cur = 0;
    progress->setValue(0);
}

void Widget::stop()
{
    stopButton->setEnabled(true);
    timer->stop();
}

void Widget::update()
{
    cur += 1;
    progress->setValue(cur);
}

Widget::~Widget()
{
    if(progress != nullptr)
        delete progress;
    if(startButton != nullptr)
        delete startButton;
    if(resetButton != nullptr)
        delete resetButton;
    if(stopButton != nullptr)
        delete stopButton;
    if(layout != nullptr)
        delete layout;
}

