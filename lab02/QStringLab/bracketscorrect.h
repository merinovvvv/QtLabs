#ifndef BRACKETSCORRECT_H
#define BRACKETSCORRECT_H

#include "command.h"
#include "task.h"

class BracketsCorrect : public Command
{
public:
    BracketsCorrect(Task& task) : _task(task) {};

    void execute() override;
private:
    Task& _task;
};

#endif // BRACKETSCORRECT_H
