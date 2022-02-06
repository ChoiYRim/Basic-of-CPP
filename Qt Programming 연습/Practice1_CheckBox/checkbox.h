#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QButtonGroup>

class CheckBox : public QWidget
{
    Q_OBJECT
public:
    CheckBox(QWidget *parent = nullptr);

    virtual ~CheckBox();

private:
    QButtonGroup *buttonGroup[2];
    QCheckBox *subjects[3];
    QCheckBox *subject_class[3];
    const char* str1[3] = {"Math","English","Science"};
    const char* str2[3] = {"A","B","C"};

private slots:
    void subjectSelected();
    //void subjectDoubleClicked(bool checked);
    void subjectClassSelected();
};
#endif // CHECKBOX_H
