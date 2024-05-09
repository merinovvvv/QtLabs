#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "widget.h"
#include "ui_widget.h"


#include "employee.h"
#include "project.h"
#include "task.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Design firm");
    setWindowIcon(QIcon(":/resource/img/money.png"));

    QPixmap background(":/resource/img/wall.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    fio = new QLineEdit();
    projectName = new QLineEdit();
    projectStart = new QLineEdit();
    projectEnd = new QLineEdit();
    taskInProject = new QLineEdit();
    taskStart = new QLineEdit();
    taskEnd = new QLineEdit();
    saveButton = new QPushButton();

    QLabel* fioLabel = new QLabel();
    fioLabel->setStyleSheet("color: white");
    fioLabel->setText("Full name:");

    QLabel* projectNameLabel = new QLabel();
    projectNameLabel->setStyleSheet("color: white");
    projectNameLabel->setText("Project name:");

    QLabel* projectStartLabel = new QLabel();
    projectStartLabel->setStyleSheet("color: white");
    projectStartLabel->setText("Start of the project:");

    QLabel* projectEndLabel = new QLabel();
    projectEndLabel->setStyleSheet("color: white");
    projectEndLabel->setText("End of the project:");


    QLabel* taskInProjectLabel = new QLabel();
    taskInProjectLabel->setStyleSheet("color: white");
    taskInProjectLabel->setText("Task in the project:");

    //QLabel* completionDateLabel  = new QLabel();
    //completionDateLabel->setText("Completion date:");

    QLabel* taskStartLabel = new QLabel();
    taskStartLabel->setStyleSheet("color: white");
    taskStartLabel->setText("Start of the task:");

    QLabel* taskEndLabel = new QLabel();
    taskEndLabel->setStyleSheet("color: white");
    taskEndLabel->setText("End of the task:");

    saveButton->setText("Save");

    QHBoxLayout* fioLayout = new QHBoxLayout();
    QHBoxLayout* projectNameLayout = new QHBoxLayout();
    QHBoxLayout* projectStartLayout = new QHBoxLayout();
    QHBoxLayout* projectEndLayout = new QHBoxLayout();
    QHBoxLayout* taskInProjectLayout = new QHBoxLayout();
    QHBoxLayout* taskStartLayout = new QHBoxLayout();
    QHBoxLayout* taskEndLayout = new QHBoxLayout();

    fioLayout->addWidget(fioLabel);
    fioLayout->addWidget(fio);

    projectNameLayout->addWidget(projectNameLabel);
    projectNameLayout->addWidget(projectName);

    projectStartLayout->addWidget(projectStartLabel);
    projectStartLayout->addWidget(projectStart);

    projectEndLayout->addWidget(projectEndLabel);
    projectEndLayout->addWidget(projectEnd);

    taskInProjectLayout->addWidget(taskInProjectLabel);
    taskInProjectLayout->addWidget(taskInProject);


    taskStartLayout->addWidget(taskStartLabel);
    taskStartLayout->addWidget(taskStart);

    taskEndLayout->addWidget(taskEndLabel);
    taskEndLayout->addWidget(taskEnd);

    // setLayout(fioLayout);
    // setLayout(projectNameLayout);
    // setLayout(taskInProjectLayout);
    // setLayout(completionDateLayout);
    // setLayout(dateOfBeginLayout);
    // setLayout(dateOfFinishLayout);


    QVBoxLayout* vertLayout = new QVBoxLayout();
    vertLayout->addLayout(fioLayout);
    vertLayout->addLayout(projectNameLayout);
    vertLayout->addLayout(projectStartLayout);
    vertLayout->addLayout(projectEndLayout);
    vertLayout->addLayout(taskInProjectLayout);
    vertLayout->addLayout(taskStartLayout);
    vertLayout->addLayout(taskEndLayout);
    vertLayout->addWidget(saveButton);

    QLineEdit* textField = new QLineEdit();
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


    QHBoxLayout* genLayout = new QHBoxLayout();


    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    genLayout->addLayout(vertLayout);
    genLayout->addItem(spacer);
    genLayout->addLayout(textAndButtons);



    setLayout(genLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveInfo()));
    connect(showTasks, SIGNAL(clicked()), this, SLOT(showTasksWindow()));
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
    employeeAndDate.insert(day->text(), employee->text());
    tasksWindow->deleteLater();
}

void Widget::saveInfo() {
    Employee *employee = new Employee();
    employee->setFullName(fio->text());

    Project *project = new Project();
    project->setProjectName(projectName->text());
    QDate startDateP = QDate::fromString(projectStart->text(), "yyyy.MM.dd");
    project->setStartDate(startDateP);
    QDate endDateP = QDate::fromString(projectEnd->text(), "yyyy.MM.dd");
    project->setStartDate(endDateP);

    Task *task = new Task();
    task->setTaskName(taskInProject->text());
    QDate startDateT = QDate::fromString(taskStart->text(), "yyyy.MM.dd");
    task->setStart(startDateT);
    QDate endDateT = QDate::fromString(taskEnd->text(), "yyyy.MM.dd");
    task->setStart(endDateT);

    employee->setProject(project);
    employee->setTask(task);

    project->addEmployee(employee);
    project->addTask(*task);

    task->setEmployee(employee);

    myCompany.addEmployee(*employee);
    myCompany.addProject(*project);

    // project = nullptr;
    // task = nullptr;
    // employee = nullptr;

    fio->clear();
    projectName->clear();
    projectStart->clear();
    projectEnd->clear();
    taskInProject->clear();
    taskStart->clear();
    taskEnd->clear();
}


Widget::~Widget()
{
    delete ui;
}


