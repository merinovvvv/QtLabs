#include "application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.setWindowTitle("miniPaint");
    w.setWindowIcon(QIcon(":/resource/img/Pencil.png"));
    w.setFixedSize(800, 800);
    w.show();
    return a.exec();
}
