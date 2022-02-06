#include "checkbox.h"
#include <QString>

CheckBox::CheckBox(QWidget* parent) : QWidget(parent)
{
    int xpos = 30;
    int ypos = 30;

    buttonGroup[0] = new QButtonGroup(this);
    buttonGroup[1] = new QButtonGroup(this);
    for(int i = 0; i < 3; i++)
    {
        subjects[i] = new QCheckBox(str1[i],this);
        subjects[i]->setGeometry(xpos,ypos,100,30);
        buttonGroup[0]->addButton(subjects[i]);

        subject_class[i] = new QCheckBox(str2[i],this);
        subject_class[i]->setGeometry(xpos+120,ypos,100,30);
        buttonGroup[1]->addButton(subject_class[i]);

        connect(subjects[i],SIGNAL(clicked()),this,SLOT(subjectSelected()));
        connect(subject_class[i],SIGNAL(clicked()),this,SLOT(subjectClassSelected()));
        ypos += 40;
    }

    buttonGroup[0]->setExclusive(false);
    buttonGroup[1]->setExclusive(true);
    subjects[0]->setIcon(QIcon(":/resources/math.png"));
    subjects[1]->setIcon(QIcon(":/resources/english.png"));
    subjects[2]->setIcon(QIcon(":/resources/science.png"));
}

void CheckBox::subjectSelected()
{
    for(int i = 0; i < 3; i++)
    {
        if(subjects[i]->isChecked())
        {
            qDebug("%s is checked...\n", str1[i]);
            //subjects[i]->setCheckState(Qt::CheckState::Unchecked);
        }
    }
}

void CheckBox::subjectClassSelected()
{
    for(int i = 0; i < 3; i++)
    {
        if(subject_class[i]->checkState())
        {
            qDebug("%s class is selected...\n", str2[i]);
        }
    }
}

CheckBox::~CheckBox()
{
    for(int i = 0; i < 3; i++)
    {
        if(subjects[i] != nullptr)
            delete subjects[i];
        if(subject_class[i] != nullptr)
            delete subject_class[i];
    }
    for(int i = 0; i < 2; i++)
    {
        if(buttonGroup[i] != nullptr)
            delete buttonGroup[i];
    }
}

