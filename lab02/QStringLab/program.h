#ifndef PROGRAM_H
#define PROGRAM_H

class Program
{
public:
    Program() = default;

    Program (const Program& other) = default;
    Program& operator= (const Program& other) = default;

    Program (Program&& other) = default;
    Program& operator= (Program&& other) = default;

    ~Program() = default;

    static int main();
};

#endif // PROGRAM_H
