#include "funnybutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FunnyButton w;
    w.show();
    return a.exec();
}
