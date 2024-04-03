#include "spawn.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Spawn w;
    w.show();
    return a.exec();
}
