#include "buttonmove.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ButtonMove w;
    w.show();
    return a.exec();
}
