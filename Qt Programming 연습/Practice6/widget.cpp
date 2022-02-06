#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    label = nullptr;
    for(size_t i = 0; i < 8; i++) fontCombo[i] = nullptr;

    int ypos = 30;

    for(size_t i = 0; i < 5; i++)
        fontCombo[i] = new QFontComboBox(this);
    fontCombo[0]->setFontFilters(QFontComboBox::AllFonts); // 모든 폰트
    fontCombo[1]->setFontFilters(QFontComboBox::ScalableFonts); // 확대/축소시 동적 자동 변환 가능한 폰트
    fontCombo[2]->setFontFilters(QFontComboBox::NonScalableFonts); // 동적 자동 변환이 제공되지 않는 폰트
    fontCombo[3]->setFontFilters(QFontComboBox::MonospacedFonts); // 일정한 문자 넓이 형태를 제공하는 폰트
    fontCombo[4]->setFontFilters(QFontComboBox::ProportionalFonts); // 넓이와 폭의 균형이 잡힌 폰트
    label = new QLabel(QString("Test Sentence."),this);

    for(size_t i = 0; i < 5; i++)
    {
        fontCombo[i]->setGeometry(10,ypos,200,30);
        ypos += 40;
    }

    connect(fontCombo[4],SIGNAL(currentIndexChanged(int)),this,SLOT(changedIndex(int)));
    connect(fontCombo[4],SIGNAL(currentFontChanged(const QFont&)),this,SLOT(changedFont(const QFont&)));
    label->setGeometry(10,ypos,200,30);
}

void Widget::changedIndex(int idx)
{
    qDebug("Font index : %d", idx);
}

void Widget::changedFont(const QFont& f)
{
    label->setFont(f.family());
}

Widget::~Widget()
{
    for(size_t i = 0; i < 8; i++)
        if(fontCombo[i] != nullptr)
            delete fontCombo[i];
    if(label != nullptr)
        delete label;

}

