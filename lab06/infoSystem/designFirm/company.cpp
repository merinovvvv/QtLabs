
#include "company.h"

Company::Company() : projects() {}

Company::~Company() {}

QList <Project> Company::getProjects() const {
    return projects;
}


void Company::addProject(const Project& project) {
    projects.append(project);
}

// Checks if a project with the specified name exists
bool Company::hasProject(const QString& projectName) const {
    for (const Project& project : projects) {
        if (project.projectName == projectName) {
            return true;
        }
    }
    return false;
}

// Adds an employee and a task to already existing project fields
void Company::addEmployeeToProject(const QString& projectName, const QString& employeeName, const Task& task) {
    for (Project& project : projects) {
        if (project.projectName == projectName) {
            for (Employee& employee : project.employees[projectName]) {
                if (employee.fullName == employeeName) {
                    // If an employee with the same name is already working on a project, add the task to his task list
                    employee.tasks.append(task);
                    return;
                }
            }
            // If the employee is not found, add him to the project
            Employee newEmployee;
            newEmployee.fullName = employeeName;
            newEmployee.tasks.append(task);
            project.employees[projectName].append(newEmployee);
            return;
        }
    }
}

// Company parseJsonFile(const QString& filePath) {

// }

