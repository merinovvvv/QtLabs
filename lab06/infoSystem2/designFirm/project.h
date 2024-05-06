#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDate>

#include "task.h"
#include "employee.h"

class Project
{
public:
    Project(QString projectName = "", QDate startDate_ = QDate(2005, 10, 28), QDate endDate = QDate(2005, 10, 28), QList<Task> tasks = {}, QList<Employee*> employees = {});

    void setProjectName(const QString&);
     QString getProjectName();


    void setStartDate(const QDate&);
    QDate getStartDate();

    void setEndDate(const QDate&);
    QDate getEndDate();

    void addTask(const Task&);
    QList<Task> getTasks();

    void addEmployee(Employee*);
    QList<Employee*> getEmployees();

    int getId();
private:
    QString projectName_;
    QDate startDate_;
    QDate endDate_;
    QList<Task> tasks_;
    QList<Employee*> employees_;

    static int id;
    int id_;
};

#endif // PROJECT_H
