#ifndef INVOKER_H
#define INVOKER_H

#include <vector>

#include "command.h"

class Invoker
{
public:
    void addCommand(Command* cmd);
    void startCommand(int taskNumber);
private:
    std::vector<Command*> _commands;
};

#endif // INVOKER_H
