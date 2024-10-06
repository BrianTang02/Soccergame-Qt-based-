#include <QApplication>
#include "Interface.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface w;
    w.setFixedSize(Interface::interface_x,Interface::interface_y);
    w.show();

    return a.exec();
}
