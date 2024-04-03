#include "widget.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setWindowTitle("tic-tac-toe");

    QIcon icon(":/images/img/icon.png");
    w.setWindowIcon(icon);

    //w.setStyleSheet("background-image: url(:/images/img/paper.jpeg); background-repeat: no-repeat; background-position: center; background-size: cover;");

    //w.setStyleSheet("background-color: lightblue;");

    //w.showFullScreen();
    w.show();
    return a.exec();
}
