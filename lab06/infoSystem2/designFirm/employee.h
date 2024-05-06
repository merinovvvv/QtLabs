#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QList>

class Project;
class Task;

class Employee
{
public:
    Employee(QString fullName = "", Project* project = nullptr, QList <Task*> tasks = {}, int totalWorkTime = 0);
    void setFullName(const QString& );
    QString getFullName();

    void setProject(Project*);
    Project* getProject();

    void setTask(Task* task);
    QList <Task*> getTasks();

    int getTotalWorkTime();
    int getId();

private:
    QString fullName_;

    Project* project_;
    QList <Task*> tasks_;

    int totalWorkTime_;

    static int id;
    int id_;


    void calcTotalWorkTime();
};

#endif // EMPLOYEE_H
