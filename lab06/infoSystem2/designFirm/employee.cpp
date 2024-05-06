#include "project.h"
#include "employee.h"

int Employee::id = 0;

Employee::Employee(QString fullName, Project* project, QList <Task*> tasks, int totalWorkTime) : fullName_(fullName), project_(project), tasks_(tasks), totalWorkTime_(totalWorkTime), id_(id) {
    project_->addEmployee(this);
    id++;
}

void Employee::setProject(Project* project) {
    project_ = project;
}

Project* Employee::getProject() {
    return project_;
}

void Employee::setTask(Task* task) {
    tasks_.append(task);
}

QList<Task*> Employee::getTasks() {
    return tasks_;
}

void Employee::setFullName(const QString& name) {
    fullName_ = name;
}

QString Employee::getFullName() {
    return fullName_;
}


int Employee::getTotalWorkTime() {
    return totalWorkTime_;
}

int Employee::getId() {
    return id_;
}



void Employee::calcTotalWorkTime() {

}
