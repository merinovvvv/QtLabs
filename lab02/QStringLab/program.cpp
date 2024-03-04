#include <QTextStream>

#include "program.h"
#include "task.h"
#include "canbuildwordnorepeat.h"
#include "canbuildwordwithrepeats.h"
#include "thelongestword.h"
#include "bracketscorrect.h"
#include "invoker.h"

int Program::main() {

    Task task1("Can build word no repeat");

    Task task2("Can build word with repeats");

    Task task3("The longest word");

    Task task4("Correct brackets");


    canBuildWordNoRepeat canBuildWordNoRepeat (task1);

    canBuildWordWithRepeats canBuildWordWithRepeats (task2);

    TheLongestWord theLongestWord (task3);

    BracketsCorrect correctBrackets (task4);

    Invoker remote;

    remote.addCommand(&canBuildWordNoRepeat);
    remote.addCommand(&canBuildWordWithRepeats);
    remote.addCommand(&theLongestWord);
    remote.addCommand(&correctBrackets);

    //remote.startCommand(0);
    remote.startCommand(3);
    //remote.startCommand(2);
    return 0;
}
