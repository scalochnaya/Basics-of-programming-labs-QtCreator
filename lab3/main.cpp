#include "calcwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calcwidget w;
    w.show();

    return a.exec();
}
