#ifndef CANBUILDWORD_H
#define CANBUILDWORD_H

#include "command.h"
#include "task.h"

class canBuildWordNoRepeat : public Command
{
public:
    canBuildWordNoRepeat(Task& task) : _task(task) {};

    void execute() override;
private:
    Task& _task;
};

#endif // CANBUILDWORD_H
