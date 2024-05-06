#ifndef COMPANY_H
#define COMPANY_H

#include "employee.h"
#include "project.h"

class Company
{
public:
    Company(QList<Employee>employees = {}, QList <Project> projects = {});
    void addEmployee(const Employee&);
    void addProject(const Project&);
    bool isEmployeeExists(const int& id);
    bool isProjectExists(const QString& projectName);
    QList <Employee> getEmployees();
    QList <Project> getProjects();
private:
    QList <Employee> employees_;
    QList <Project> projects_;
};

#endif // COMPANY_H
