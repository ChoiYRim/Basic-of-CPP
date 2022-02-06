#include "checkbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    CheckBox w;

    w.show();

    return a.exec();
}
