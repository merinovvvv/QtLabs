#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

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
    QLineEdit* taskInProject;
    //QLineEdit* completionDate;
    QLineEdit* dateOfBegin;
    QLineEdit* dateOfFinish;
    QPushButton* saveButton;
    QWidget *tasksWindow;
    QMap <QString, QString> employeeAndDate;
    QLineEdit* day;
    QLineEdit* employee;
    void writeToJsonFile(const QString& fileName, const QList<QString>& companyInfo);

private slots:
    void saveCompanyInfo();
    void showTasksWindow();
    void backToMain();
};
#endif // WIDGET_H
