#include "mdimainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MDIMainWindow w;
    w.show();
    return a.exec();
}
