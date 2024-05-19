#ifndef DRAWFIGURE_H
#define DRAWFIGURE_H

#include "command.h"
#include "receiver.h"

class drawFigure : public Command
{
public:
    drawFigure();
private:
    Receiver& drawType;
};

#endif // DRAWFIGURE_H
