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

    setWindowTitle("Design firm");
    setWindowIcon(QIcon(":/resource/img/money.png"));

    QPixmap background(":/resource/img/wall.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    fio = new QLineEdit();
    projectName = new QLineEdit();
    taskInProject = new QLineEdit();
    //completionDate = new QLineEdit();
    dateOfBegin = new QLineEdit();
    dateOfFinish = new QLineEdit();
    saveButton = new QPushButton();

    QLabel* fioLabel = new QLabel();
    fioLabel->setStyleSheet("color: white");
    fioLabel->setText("Full name:");

    QLabel* projectNameLabel = new QLabel();
    projectNameLabel->setStyleSheet("color: white");
    projectNameLabel->setText("Project name:");

    QLabel* taskInProjectLabel = new QLabel();
    taskInProjectLabel->setStyleSheet("color: white");
    taskInProjectLabel->setText("Task in the project:");

    //QLabel* completionDateLabel  = new QLabel();
    //completionDateLabel->setText("Completion date:");

    QLabel* dateOfBeginLabel = new QLabel();
    dateOfBeginLabel->setStyleSheet("color: white");
    dateOfBeginLabel->setText("Start date:");

    QLabel* dateOfFinishLabel = new QLabel();
    dateOfFinishLabel->setStyleSheet("color: white");
    dateOfFinishLabel->setText("Finish date:");

    saveButton->setText("Save");

    QHBoxLayout* fioLayout = new QHBoxLayout();
    QHBoxLayout* projectNameLayout = new QHBoxLayout();
    QHBoxLayout* taskInProjectLayout = new QHBoxLayout();
    //QHBoxLayout* completionDateLayout = new QHBoxLayout();
    QHBoxLayout* dateOfBeginLayout = new QHBoxLayout();
    QHBoxLayout* dateOfFinishLayout = new QHBoxLayout();

    fioLayout->addWidget(fioLabel);
    fioLayout->addWidget(fio);

    projectNameLayout->addWidget(projectNameLabel);
    projectNameLayout->addWidget(projectName);

    taskInProjectLayout->addWidget(taskInProjectLabel);
    taskInProjectLayout->addWidget(taskInProject);

    //completionDateLayout->addWidget(completionDateLabel);
    //completionDateLayout->addWidget(completionDate);

    dateOfBeginLayout->addWidget(dateOfBeginLabel);
    dateOfBeginLayout->addWidget(dateOfBegin);

    dateOfFinishLayout->addWidget(dateOfFinishLabel);
    dateOfFinishLayout->addWidget(dateOfFinish);

    // setLayout(fioLayout);
    // setLayout(projectNameLayout);
    // setLayout(taskInProjectLayout);
    // setLayout(completionDateLayout);
    // setLayout(dateOfBeginLayout);
    // setLayout(dateOfFinishLayout);


    QVBoxLayout* vertLayout = new QVBoxLayout();
    vertLayout->addLayout(fioLayout);
    vertLayout->addLayout(projectNameLayout);
    vertLayout->addLayout(taskInProjectLayout);
    //vertLayout->addLayout(completionDateLayout);
    vertLayout->addLayout(dateOfBeginLayout);
    vertLayout->addLayout(dateOfFinishLayout);
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

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCompanyInfo()));
    connect(showTasks, SIGNAL(clicked()), this, SLOT(showTasksWindow()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::saveCompanyInfo() {
    QList <QString> tmp = Company::getCompanyInfo();
    tmp.append(fio->text());
    tmp.append(projectName->text());
    tmp.append(taskInProject->text());
    tmp.append(dateOfBegin->text());
    tmp.append(dateOfFinish->text());
    //tmp.append(" ");
    Company::setCompanyInfo(tmp);


    QString fileName = "companyInfo.json";
    writeToJsonFile(fileName, companyInfo);
    fio->clear();
    projectName->clear();
    taskInProject->clear();
    dateOfBegin->clear();
    dateOfFinish->clear();
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

QJsonArray convertToJsonObject(const QList<QString> &companyInfo) {
    QJsonArray jsonArray;
    int numFields = 5; // Ожидаемое количество полей в каждой строке
    for (int i = 0; i < companyInfo.size(); i += numFields) {
        if (i + numFields <= companyInfo.size()) { // Проверка, достаточно ли элементов для создания объекта
            QJsonObject obj;
            obj["employee"] = companyInfo[i];
            obj["project"] = companyInfo[i + 1];
            obj["task"] = companyInfo[i + 2];
            obj["start date"] = companyInfo[i + 3];
            obj["end date"] = companyInfo[i + 4];
            jsonArray.append(obj);
        } else {
            qWarning() << "Insufficient data to create object at index:" << i;
        }
    }
    return jsonArray;
}



void Widget::writeToJsonFile(const QString& fileName, const QList<QString>& companyInfo) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open file for writing:" << fileName;
        return;
    }

    QTextStream out(&file);
    QJsonArray jsonArray = convertToJsonObject(companyInfo);
    for (const QJsonValue &value : jsonArray) {
        QVariantMap map = value.toObject().toVariantMap();
        QJsonObject obj = QJsonObject::fromVariantMap(map);
        out << QJsonDocument(obj).toJson(QJsonDocument::Indented) << endl;
    }

    file.close();
}
