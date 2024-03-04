#ifndef TASK_H
#define TASK_H

#include <string>

#include "intermediatefunctions.h"

//simmilar to Receiver
class Task : public IntermediateFunctions
{
public:
    Task(const std::string &name) : _taskName(name) {};

    void canBuildWordNoRepeat ();

    void canBuildWordWithRepeats ();

    void TheLongestWord ();

    void BracketsCorrect ();

private:
    std::string _taskName;
};

#endif // TASK_H
