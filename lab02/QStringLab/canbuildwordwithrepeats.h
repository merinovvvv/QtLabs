#ifndef CANBUILDWORDWITHREPEATS_H
#define CANBUILDWORDWITHREPEATS_H

#include "command.h"
#include "task.h"

class canBuildWordWithRepeats : public Command
{
public:
    canBuildWordWithRepeats(Task& task) : _task(task) {};

    void execute() override;
private:
    Task& _task;
};

#endif // CANBUILDWORDWITHREPEATS_H
