#include "widget.h"
#include <QScreen>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.showFullScreen();
    return a.exec();
}
