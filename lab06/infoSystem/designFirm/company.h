#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QList>

#include <QDate>
#include <QMap>

struct Task {
    QString taskName;
    QDate completionDate;
};

struct Employee {
    QString fullName;
    QList<Task> tasks;
};

struct Project {
    QString projectName;
    QDate startDate;
    QDate endDate;
    QMap<QString, QList<Employee>> employees; // Сотрудники для каждого проекта
};

class Company
{
public:
    Company();
    ~Company();

    void addProject(const Project& project);
    QList <Project> getProjects() const;

    bool hasProject(const QString& projectName) const;

    void addEmployeeToProject(const QString& projectName, const QString& employeeName, const Task& task);

private:
    QList <Project> projects;
};

#endif // COMPANY_H
