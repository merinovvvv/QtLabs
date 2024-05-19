#ifndef RECEIVER_H
#define RECEIVER_H

#include <QString>

class Receiver
{
public:
    //Receiver();

    void pencilDraw();
    void figureDraw();
    void textDraw();

private:
    QString commandName;
    //maybe QList commands
};

#endif // RECEIVER_H
