#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <QString>

#include "employee.h"


class Task
{
public:
    Task(QString taskName = "", QDate startDate = QDate(2005, 10, 28), QDate endDate = QDate(2005, 10, 28), Employee* employee = {});
    void setTaskName(const QString&);
    void setStart(const QDate&);
    void setEnd(const QDate&);
    void setEmployee(Employee* employee);
    QString getTaskName();
    QDate getStartDate();
    QDate getEndDate();
    Employee* getEmployee();
    int getId();

private:
    QString taskName_;

    static int id;
    int id_;

    QDate startDate_;
    QDate endDate_;
    Employee* employee_;
};

#endif // TASK_H
