#include <QVBoxLayout>
#include <QLabel>

#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Company company;

    myCompany = Company::parseJsonFile("companyInfo.json");

    setWindowTitle("Design firm");
    setWindowIcon(QIcon(":/resource/img/money.png"));

    QPixmap background(":/resource/img/wall.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    fio = new QLineEdit();
    projectName = new QLineEdit();
    projectStartDate = new QLineEdit();
    projectEndDate = new QLineEdit();
    taskName = new QLineEdit();
    completionDate = new QLineEdit();
    saveButton = new QPushButton();

    QLabel* fioLabel = new QLabel();
    fioLabel->setStyleSheet("color: white");
    fioLabel->setText("Full name:");

    QLabel* projectNameLabel = new QLabel();
    projectNameLabel->setStyleSheet("color: white");
    projectNameLabel->setText("Project name:");

    QLabel* projectStartDateLabel = new QLabel();
    projectStartDateLabel->setStyleSheet("color: white");
    projectStartDateLabel->setText("Project start date:");

    QLabel* projectEndDateLabel = new QLabel();
    projectEndDateLabel->setStyleSheet("color: white");
    projectEndDateLabel->setText("Project end date:");

    QLabel* taskNameLabel = new QLabel();
    taskNameLabel->setStyleSheet("color: white");
    taskNameLabel->setText("Task name:");

    QLabel* completionDateLabel  = new QLabel();
    completionDateLabel->setStyleSheet("color: white");
    completionDateLabel->setText("Completion date:");

    saveButton->setText("Save");

    QHBoxLayout* fioLayout = new QHBoxLayout();
    QHBoxLayout* projectNameLayout = new QHBoxLayout();
    QHBoxLayout* projectStartDateLayout = new QHBoxLayout();
    QHBoxLayout* projectEndDateLayout = new QHBoxLayout();
    QHBoxLayout* taskNameLayout = new QHBoxLayout();
    QHBoxLayout* completionDateLayout = new QHBoxLayout();

    fioLayout->addWidget(fioLabel);
    fioLayout->addWidget(fio);

    projectNameLayout->addWidget(projectNameLabel);
    projectNameLayout->addWidget(projectName);

    projectStartDateLayout->addWidget(projectStartDateLabel);
    projectStartDateLayout->addWidget(projectStartDate);

    projectEndDateLayout->addWidget(projectEndDateLabel);
    projectEndDateLayout->addWidget(projectEndDate);

    taskNameLayout->addWidget(taskNameLabel);
    taskNameLayout->addWidget(taskName);

    completionDateLayout->addWidget(completionDateLabel);
    completionDateLayout->addWidget(completionDate);

    // setLayout(fioLayout);
    // setLayout(projectNameLayout);
    // setLayout(taskInProjectLayout);
    // setLayout(completionDateLayout);
    // setLayout(dateOfBeginLayout);
    // setLayout(dateOfFinishLayout);


    QVBoxLayout* vertLayout = new QVBoxLayout();
    vertLayout->addLayout(fioLayout);
    vertLayout->addLayout(projectNameLayout);
    vertLayout->addLayout(projectStartDateLayout);
    vertLayout->addLayout(projectEndDateLayout);
    vertLayout->addLayout(taskNameLayout);
    vertLayout->addLayout(completionDateLayout);
    vertLayout->addWidget(saveButton);

    textField = new QPlainTextEdit();
    //genLayout->addWidget(textField);
    textField->setFixedHeight(200);


    QVBoxLayout* textAndButtons = new QVBoxLayout();
    textAndButtons->addWidget(textField);


    QPushButton* showProjects = new QPushButton();
    showProjects->setText("Show all projects");
    textAndButtons->addWidget(showProjects);

    QPushButton* showTasks = new QPushButton();
    showTasks->setText("Show an employee's task list for the current day");
    textAndButtons->addWidget(showTasks);

    QPushButton* showEmployees = new QPushButton();
    showEmployees->setText("Show a list of employees");
    textAndButtons->addWidget(showEmployees);

    QPushButton* clearButton = new QPushButton();
    clearButton->setText("Clear");
    textAndButtons->addWidget(clearButton);


    QHBoxLayout* genLayout = new QHBoxLayout();


    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    genLayout->addLayout(vertLayout);
    genLayout->addItem(spacer);
    genLayout->addLayout(textAndButtons);



    setLayout(genLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCompanyInfo()));
    connect(showTasks, SIGNAL(clicked()), this, SLOT(showTasksWindow()));
    connect (showProjects, SIGNAL(clicked()), this, SLOT(showSortedProjects()));
    connect (showEmployees, SIGNAL(clicked()), this, SLOT(showEmployees()));
    connect (clearButton, SIGNAL(clicked()), this, SLOT(clearTextField()));

}

void Widget::saveCompanyInfo() {

    Task task;
    task.taskName = taskName->text();
    QDate tCompletionDate = QDate::fromString(completionDate->text(), "yyyy-MM-dd");
    task.completionDate = tCompletionDate;

    bool projectExists = myCompany.hasProject(projectName->text());

    if (projectExists) {
        // If the project exists
        myCompany.addEmployeeToProject(projectName->text(), fio->text(), task);
    } else {

        Project project;
        project.projectName = projectName->text();
        QDate pStartDate = QDate::fromString(projectStartDate->text(), "yyyy-MM-dd");
        project.startDate = pStartDate;
        QDate pEndDate = QDate::fromString(projectEndDate->text(), "yyyy-MM-dd");
        project.endDate = pEndDate;

        Employee employee;
        employee.fullName = fio->text();


        employee.tasks.append(task);
        project.employees[project.projectName].append(employee);

        myCompany.addProject(project);

    }

    QString fileName = "companyInfo.json";

    writeToJsonFile(fileName, myCompany);
    fio->clear();
    projectName->clear();
    projectStartDate->clear();
    projectEndDate->clear();
    taskName->clear();
    completionDate->clear();
}

// Converts the data structure to JSON
// QJsonObject Widget::projectToJson(const Project& project) {
//     QJsonObject projectObject;
//     projectObject["projectName"] = project.projectName;

//     QString startDateString = project.startDate.toString("yyyy-MM-dd");
//     projectObject["startDate"] = startDateString;

//     QString endDateString = project.endDate.toString("yyyy-MM-dd");
//     projectObject["endDate"] = endDateString;

//     QJsonObject employeesObject;



//     for (const QString& projectName : project.employees.keys()) {
//         QJsonArray employeeArray;
//         for (const Employee& employee : project.employees.value(projectName)) {
//             QJsonObject employeeObject;
//             employeeObject["fullName"] = employee.fullName;

//             QJsonArray tasksArray;
//             for (const Task& task : employee.tasks) {
//                 QJsonObject taskObject;
//                 taskObject["taskName"] = task.taskName;

//                 QString completionDateString = task.completionDate.toString("yyyy-MM-dd");
//                 taskObject["completionDate"] = completionDateString;
//                 tasksArray.append(taskObject);
//             }
//             employeeObject["tasks"] = tasksArray;

//             employeeArray.append(employeeObject);
//         }
//         employeesObject[projectName] = employeeArray;
//     }
//     projectObject["employees"] = employeesObject;

//     return projectObject;
// }

//Converts the company to JSON
QJsonObject Widget::companyToJson(const Company& company) {
    QJsonObject companyObject;

    QJsonArray projectsArray;
    for (const Project& project : company.getProjects()) {
        QJsonObject projectObject;
        projectObject["projectName"] = project.projectName;
        projectObject["startDate"] = project.startDate.toString("yyyy-MM-dd");
        projectObject["endDate"] = project.endDate.toString("yyyy-MM-dd");

        QJsonArray employeesArray;

        //qDebug() << "Number of projects in project.employees:" << project.employees.size();

        for (const auto& employeeList : project.employees) {
            for (const Employee& employee : employeeList) {
                QJsonObject employeeObject;
                employeeObject["fullName"] = employee.fullName;

                QJsonArray tasksArray;
                for (const Task& task : employee.tasks) {
                    QJsonObject taskObject;
                    taskObject["taskName"] = task.taskName;
                    taskObject["completionDate"] = task.completionDate.toString("yyyy-MM-dd");
                    tasksArray.append(taskObject);
                }
                employeeObject["tasks"] = tasksArray;

                employeesArray.append(employeeObject);
            }
        }

        projectObject["employees"] = employeesArray;
        projectsArray.append(projectObject);
    }

    companyObject["company"] = projectsArray;

    return companyObject;
}


// Writes JSON to a file
void Widget::writeToJsonFile(const QString& fileName, const Company& company) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open file for writing:" << fileName;
        return;
    }

    QTextStream out(&file);
    QJsonDocument jsonDoc(companyToJson(company));
    out << jsonDoc.toJson(QJsonDocument::Indented);

    file.close();
}


void Widget::showTasksWindow() {
    tasksWindow = new QWidget();
    tasksWindow->setWindowTitle("Task list");
    tasksWindow->resize(500, 500);
    tasksWindow->setWindowIcon(QIcon(":/resource/img/list.png"));
    tasksWindow->show();

    QPixmap tasksWindowBackground(":/resource/img/tasksWall.png");
    QPalette tasksWindowPalette;
    tasksWindowPalette.setBrush(QPalette::Window, tasksWindowBackground);
    tasksWindow->setPalette(tasksWindowPalette);

    QHBoxLayout* taskWindowHLayout1 = new QHBoxLayout();
    QLabel* input1 = new QLabel();
    input1->setStyleSheet("color: white");
    input1->setText("Employee's full name:");
    employee = new QLineEdit();
    taskWindowHLayout1->addWidget(input1);
    taskWindowHLayout1->addWidget(employee);

    QHBoxLayout* taskWindowHLayout2 = new QHBoxLayout();
    QLabel* input2 = new QLabel();
    input2->setStyleSheet("color: white");
    input2->setText("Day of working:");
    day = new QLineEdit();
    taskWindowHLayout2->addWidget(input2);
    taskWindowHLayout2->addWidget(day);

    QPushButton* taskWindowConfirmButton = new QPushButton();
    taskWindowConfirmButton->setText("Confirm");

    QVBoxLayout* taskWindowVLayout = new QVBoxLayout();
    taskWindowVLayout->addLayout(taskWindowHLayout1);
    taskWindowVLayout->addLayout(taskWindowHLayout2);
    taskWindowVLayout->addWidget(taskWindowConfirmButton);

    tasksWindow->setLayout(taskWindowVLayout);

    connect (taskWindowConfirmButton, SIGNAL(clicked()), this, SLOT(backToMain()));
}

void Widget::backToMain() {

    QDate secondWindowDate_ = QDate::fromString(day->text(), "yyyy-MM-dd");

    secondWindowDate = secondWindowDate_;

    secondWindowEmployee = employee->text();

    //qDebug() << secondWindowEmployee << secondWindowDate;

    tasksWindow->deleteLater();

    QList<Project> projects = myCompany.getProjects();

    qDebug() << "secondWindowEmployee:" << secondWindowEmployee;


    QStringList employeeTasksForToday;


    for (const Project &project : projects) {
        for (auto it = project.employees.begin(); it != project.employees.end(); ++it) {
            for (const Employee &employee : it.value()) {
                if (employee.fullName == secondWindowEmployee) {
                    for (const Task &task : employee.tasks) {
                        if (secondWindowDate >= project.startDate && secondWindowDate <= task.completionDate) {
                            employeeTasksForToday.append(task.taskName);
                        }
                    }
                }
            }
        }
    }



    //qDebug() << "Size of employeeTasksForToday: " << employeeTasksForToday.size();

    QString secondWindowDateString = secondWindowDate.toString("yyyy-MM-dd");

    QString resultText = QString("Tasks for employee %1 for %2:\n").arg(secondWindowEmployee).arg(secondWindowDateString);
    for (const QString &task : employeeTasksForToday) {
        resultText += QString("- %1\n").arg(task);
    }

    textField->setPlainText(resultText);
}

void Widget::showSortedProjects() {
    QList <Project> projects = myCompany.getProjects();

    std::sort(projects.begin(), projects.end(), [](const Project &a, const Project &b) {
        return a.endDate < b.endDate;
    });

    QString allProjectsText;

    for (const Project &project : projects) {
        QString text = QString("Project name: %1\n").arg(project.projectName);

        allProjectsText += text;
    }
    textField->setPlainText(allProjectsText);
}

void Widget::showEmployees() {
    employeesWindow = new QWidget();
    employeesWindow->setWindowTitle("Month work");
    employeesWindow->resize(500, 500);
    employeesWindow->setWindowIcon(QIcon(":/resource/img/employeeIcon.png"));
    employeesWindow->show();

    QPixmap employeesWindowBackground(":/resource/img/tasksWall.png");
    QPalette employeesWindowPalette;
    employeesWindowPalette.setBrush(QPalette::Window, employeesWindowBackground);
    employeesWindow->setPalette(employeesWindowPalette);

    QHBoxLayout* employeeWindowHLayout = new QHBoxLayout();
    QLabel* inputMonth = new QLabel();
    inputMonth->setStyleSheet("color: white");
    inputMonth->setText("Input the month number:");
    month = new QLineEdit();
    employeeWindowHLayout->addWidget(inputMonth);
    employeeWindowHLayout->addWidget(month);

    QHBoxLayout* employeeWindowHLayout2 = new QHBoxLayout();
    QLabel* inputYear = new QLabel();
    inputYear->setStyleSheet("color: white");
    inputYear->setText("Input the year:");
    year = new QLineEdit();
    employeeWindowHLayout2->addWidget(inputYear);
    employeeWindowHLayout2->addWidget(year);

    QPushButton* employeesWindowConfirmButton = new QPushButton();
    employeesWindowConfirmButton->setText("Confirm");

    QVBoxLayout* employeeWindowVLayout = new QVBoxLayout();
    employeeWindowVLayout->addLayout(employeeWindowHLayout);
    employeeWindowVLayout->addLayout(employeeWindowHLayout2);
    employeeWindowVLayout->addWidget(employeesWindowConfirmButton);

    employeesWindow->setLayout(employeeWindowVLayout);

    connect(employeesWindowConfirmButton, SIGNAL(clicked()), this, SLOT(calculateAndDisplayEmployeeWork()));
}

void Widget::calculateAndDisplayEmployeeWork() {
    employeesWindow->deleteLater();

    int targetMonth = month->text().toInt();
    int targetYear = year->text().toInt();

    QDate firstDayOfMonth(targetYear, targetMonth, 1);

    QDate tmpLastDayOfMonth(targetYear, targetMonth, 1);
    int intLastDayOfMonth = tmpLastDayOfMonth.daysInMonth();

    QDate lastDayOfMonth(targetYear, targetMonth, intLastDayOfMonth);

    QMap<QString, int> employeeWork;

    for (const Project &project : myCompany.getProjects()) {
        for (const auto &employeeList : project.employees) {
            for (const Employee &employee : employeeList) {
                int daysDifference = 0;
                for (const Task &task : employee.tasks) {
                    if (project.startDate.year() == targetYear && task.completionDate.year() == targetYear) {
                        if (project.startDate.month() == targetMonth && task.completionDate.month() == targetMonth) {
                            daysDifference = std::abs(task.completionDate.daysTo(project.startDate)) + 1;
                        } else if (project.startDate.month() < targetMonth && task.completionDate.month() == targetMonth) {
                            daysDifference = std::abs(task.completionDate.daysTo(firstDayOfMonth)) + 1;
                        } else if (project.startDate.month() == targetMonth && task.completionDate.month() > targetMonth) {
                            daysDifference = std::abs(task.completionDate.daysTo(lastDayOfMonth)) + 1;
                        } else if (project.startDate.month() < targetMonth && task.completionDate.month() > targetMonth) {
                            daysDifference = std::abs(lastDayOfMonth.daysTo(firstDayOfMonth)) + 1;
                        } else {
                            daysDifference = 0;
                        }
                    } else if (project.startDate.year() < targetYear && task.completionDate.year() == targetYear) {
                        if (targetMonth == task.completionDate.month()) {
                            daysDifference = std::abs(task.completionDate.daysTo(firstDayOfMonth)) + 1;
                        } else if (targetMonth < task.completionDate.month()) {
                            daysDifference = std::abs(lastDayOfMonth.daysTo(firstDayOfMonth)) + 1;
                        } else {
                            daysDifference = 0;
                        }
                    } else if (project.startDate.year() == targetYear && targetYear < task.completionDate.year()) {
                        if (project.startDate.month() == targetMonth) {
                            daysDifference = std::abs(lastDayOfMonth.daysTo(project.startDate)) + 1;
                        } else if (project.startDate.month() < targetMonth) {
                            daysDifference = std::abs(lastDayOfMonth.daysTo(firstDayOfMonth)) + 1;
                        } else {
                            daysDifference = 0;
                        }
                    } else if (project.startDate.year() < targetYear && targetYear < task.completionDate.year()) {
                        daysDifference = std::abs(lastDayOfMonth.daysTo(firstDayOfMonth)) + 1;
                    } else {
                        daysDifference = 0;
                    }
                    employeeWork[employee.fullName] += daysDifference;
                }
            }
        }
    }



    QString resultText = "Employees and their total work days for month № " + QString::number(targetMonth) + ":\n";
    for (const QString &employeeName : employeeWork.keys()) {
        resultText += QString("%1: %2 days\n").arg(employeeName).arg(employeeWork.value(employeeName));
    }

    textField->setPlainText(resultText);
}

void Widget::clearTextField() {
    textField->clear();
}

Widget::~Widget()
{
    delete ui;
}
