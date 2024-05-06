#include "project.h"
#include "employee.h"

int Project::id = 0;

Project::Project(QString projectName, QDate startDate, QDate endDate, QList<Task> tasks, QList<Employee*> employees) : projectName_(projectName), startDate_(startDate), endDate_ (endDate), tasks_(tasks), employees_(employees), id_(id){
    for (size_t i = 0; i < employees_.size(); ++i) {
        employees_[i]->setProject(this);
    }
    id++;
}

// Project::~Project() {
//     for (Employee* emp : employees_) {
//         delete emp;
//     }
//     employees_.clear();
// }

void Project::setProjectName(const QString& name) {
    projectName_ = name;
}

void Project::setStartDate(const QDate& date) {
    startDate_ = date;
}
void Project::setEndDate(const QDate& date) {
    endDate_ = date;
}

void Project::addTask(const Task& task) {
    tasks_.append(task);
}

void Project::addEmployee(Employee* employee) {
    employees_.append(employee);
}

QString Project::getProjectName() {
    return projectName_;
}

QDate Project::getStartDate() {
    return startDate_;
}

QDate Project::getEndDate() {
    return endDate_;
}

QList<Task> Project::getTasks() {
    return tasks_;
}

QList<Employee*> Project::getEmployees() {
    return employees_;
}

int Project::getId() {
    return id_;
}
