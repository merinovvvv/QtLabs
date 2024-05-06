#include "company.h"
#include "employee.h"

Company::Company(QList<Employee>employees, QList <Project> projects) : employees_(employees), projects_(projects) {}

// Company::~Company() {}

void Company::addEmployee(const Employee& employee) {
    employees_.append(employee);
}

void Company::addProject(const Project& projectName) {
    projects_.append(projectName);
}

bool Company::isEmployeeExists(const int& id) {
    for (size_t i = 0; i < employees_.size(); ++i) {
        if (employees_[i].getId() == id) {
            return true;
        }
    }
    return false;
}

bool Company::isProjectExists(const QString& projectName) {
    for (size_t i = 0; i < projects_.size(); ++i) {
        if (projects_[i].getProjectName() == projectName) {
            return true;
        }
    }
    return false;
}

QList<Employee> Company::getEmployees() {
    return employees_;
}

QList<Project> Company::getProjects() {
    return projects_;
}
