#include "logiclac.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logiclac w;
    w.show();

    return a.exec();
}
