#include "invoker.h"
#include <stdexcept>

void Invoker::addCommand (Command* cmd) {
    _commands.push_back(cmd);
}

void Invoker::startCommand(int taskNumber) {
    if (taskNumber >= 0 && taskNumber < _commands.size()) {
        _commands[taskNumber]->execute();
    }
    else {
        throw std::logic_error("There is no such task.");
    }
}
