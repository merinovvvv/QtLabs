#include "patterns.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Patterns w;
    w.resize(960, 540);
    w.setWindowTitle("Array's histograms using Patterns");
    w.setStyleSheet("background-color: lightblue;");
    w.show();
    return a.exec();
}
