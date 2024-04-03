#include "buttonsandboxes.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ButtonsAndBoxes w;
    w.show();
    return a.exec();
}
