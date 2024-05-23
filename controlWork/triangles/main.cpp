#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // w.setWindowTitle("Triangles");
    // w.setWindowIcon(QIcon(":/resource/img/triangle.png"));
    w.setFixedSize(1200, 800);
    w.show();
    return a.exec();
}
