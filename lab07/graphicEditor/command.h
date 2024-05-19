#ifndef COMMAND_H
#define COMMAND_H

#include <QtMath>

class Command
{
public:
    Command();

    virtual void execute() = 0;

    void undo();
    void SaveBackup();

private:

};

#endif // COMMAND_H
