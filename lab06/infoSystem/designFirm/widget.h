#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>

#include "company.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget, public Company
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;
    QLineEdit* fio;
    QLineEdit* projectName;
    QLineEdit* projectStartDate;
    QLineEdit* projectEndDate;
    QLineEdit* taskName;
    QLineEdit* completionDate;
    QPlainTextEdit* textField;
    QLineEdit* day;
    QLineEdit* employee;

    QPushButton* saveButton;

    QWidget *tasksWindow;
    QDate secondWindowDate;
    QString secondWindowEmployee;

    QWidget *employeesWindow;
    QLineEdit* month;
    QLineEdit* year;

    Company myCompany;
    void writeToJsonFile(const QString& fileName, const Company& company);
    QJsonObject companyToJson(const Company& company);
    QJsonObject projectToJson(const Project& project);

private slots:
    void saveCompanyInfo();
    void showTasksWindow();
    void backToMain();
    void showSortedProjects();
    void showEmployees();
    void calculateAndDisplayEmployeeWork();
    void clearTextField();
};
#endif // WIDGET_H
