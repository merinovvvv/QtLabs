#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "task.h"
#include "employee.h"
#include "project.h"
#include "company.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget//, public Employee, public Project, public Task, public Company
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QLineEdit* fio;
    QLineEdit* projectName;
    QLineEdit* taskInProject;
    QLineEdit* projectStart;
    QLineEdit* projectEnd;
    QLineEdit* taskStart;
    QLineEdit* taskEnd;
    QPushButton* saveButton;

    QWidget *tasksWindow;
    QMap <QString, QString> employeeAndDate;
    QLineEdit* day;
    QLineEdit* employee;

    Employee *myEmployee;
    Project *myProject;
    Task *myTask;
    Company *myCompany;

private slots:
    void showTasksWindow();
    // void saveEmployee();
    // void saveTask();
    // void saveProject();
};
#endif // WIDGET_H
