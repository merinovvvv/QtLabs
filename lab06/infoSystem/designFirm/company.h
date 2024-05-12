#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QList>

#include <QDate>
#include <QMap>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>


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

    static Company parseJsonFile(const QString& filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open file:" << file.errorString();
            return Company();
        }

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (jsonDoc.isNull() || jsonDoc.isEmpty() || !jsonDoc.isObject()) {
            qDebug() << "Failed to create JSON document or JSON is not an object";
            return Company();
        }

        Company company;
        QJsonObject jsonObj = jsonDoc.object();
        if (jsonObj.contains("company") && jsonObj["company"].isArray()) {
            QJsonArray companyArray = jsonObj["company"].toArray();
            for (const auto& companyObj : companyArray) {
                if (companyObj.isObject()) {
                    QJsonObject projectObj = companyObj.toObject();
                    Project project;
                    project.projectName = projectObj["projectName"].toString();
                    project.startDate = QDate::fromString(projectObj["startDate"].toString(), "yyyy-MM-dd");
                    project.endDate = QDate::fromString(projectObj["endDate"].toString(), "yyyy-MM-dd");

                    // Parse employees
                    if (projectObj.contains("employees") && projectObj["employees"].isArray()) {
                        QJsonArray employeesArray = projectObj["employees"].toArray();
                        for (const auto& employeeObj : employeesArray) {
                            if (employeeObj.isObject()) {
                                QJsonObject employeeJson = employeeObj.toObject();
                                Employee employee;
                                employee.fullName = employeeJson["fullName"].toString();

                                // Parse tasks
                                if (employeeJson.contains("tasks") && employeeJson["tasks"].isArray()) {
                                    QJsonArray tasksArray = employeeJson["tasks"].toArray();
                                    for (const auto& taskObj : tasksArray) {
                                        if (taskObj.isObject()) {
                                            QJsonObject taskJson = taskObj.toObject();
                                            Task task;
                                            task.taskName = taskJson["taskName"].toString();
                                            task.completionDate = QDate::fromString(taskJson["completionDate"].toString(), "yyyy-MM-dd");
                                            employee.tasks.append(task);
                                        }
                                    }
                                }
                                project.employees[project.projectName].append(employee);
                            }
                        }
                    }
                    company.addProject(project);
                }
            }
        }

        return company;
    }

private:
    QList <Project> projects;
};

#endif // COMPANY_H
