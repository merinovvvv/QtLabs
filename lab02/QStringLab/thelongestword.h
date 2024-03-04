#ifndef THELONGESTWORD_H
#define THELONGESTWORD_H

#include "command.h"
#include "task.h"

class TheLongestWord : public Command
{
public:
    TheLongestWord(Task& task) : _task(task) {};

    void execute() override;
private:
    Task& _task;
};

#endif // THELONGESTWORD_H
