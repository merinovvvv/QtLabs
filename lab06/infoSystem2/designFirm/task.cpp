#include "task.h"

int Task::id = 0;

Task::Task(QString taskName, QDate startDate, QDate endDate, Employee* employee) : taskName_(taskName), id_(id), startDate_(startDate), endDate_(endDate), employee_(employee) {
    employee->setTask(this);
    id++;
}

Task::~Task() {
    delete employee_;
}

void Task::setTaskName(const QString& name) {
    taskName_ = name;
}

void Task::setStart(const QDate& date) {
    startDate_ = date;
}

void Task::setEnd(const QDate& date) {
    endDate_ = date;
}

void Task::setEmployee(Employee* employee) {
    employee->setTask(this);
}

QString Task::getTaskName() {
    return taskName_;
}

QDate Task::getStartDate() {
    return startDate_;
}

QDate Task::getEndDate() {
    return endDate_;
}

Employee* Task::getEmployee() {
    return employee_;
}

int Task::getId() {
    return id_;
}

