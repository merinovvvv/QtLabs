#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QGraphicsPolygonItem>
#include <QDebug>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Triangles");
    setWindowIcon(QIcon(":/resource/img/triangle.png"));

    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *paramsMenu = new QMenu("Parameters", this);

    listWidget = new QListWidget();

    pattern1 = new QCheckBox();
    pattern2 = new QCheckBox();
    pattern3 = new QCheckBox();

    // QLabel* pattern1Label = new QLabel();
    // QLabel* pattern2Label = new QLabel();
    // QLabel* pattern3Label = new QLabel();

    pattern1->setText("CrossPattern");
    pattern2->setText("Dense7Pattern");
    pattern3->setText("HorPattern");

    QHBoxLayout* patternsLayout = new QHBoxLayout();
    patternsLayout->addWidget(pattern1);
    patternsLayout->addWidget(pattern2);
    patternsLayout->addWidget(pattern3);

    chooseBrushColorAction = new QAction("Brush color", this);
    choosePenColorAction = new QAction("Pen color", this);
    paramsMenu->addAction(choosePenColorAction);
    paramsMenu->addAction(chooseBrushColorAction);

    QAction *about = new QAction("About", menuBar);

    QAction *quit = new QAction("Quit", menuBar);

    menuBar->addMenu(paramsMenu);
    menuBar->addAction(about);
    menuBar->addAction(quit);

    setMenuBar(menuBar);

    canvas = new QGraphicsScene();
    canvasView = new QGraphicsView();

    canvas->setSceneRect(0, 0, 750, 650);
    canvasView->setScene(canvas);

    x1Line = new QLineEdit();
    x2Line = new QLineEdit();
    x3Line = new QLineEdit();

    y1Line = new QLineEdit();
    y2Line = new QLineEdit();
    y3Line = new QLineEdit();

    QLabel* typeLabel = new QLabel();
    typeLabel->setText("Triangle type:");

    typeLine = new QLineEdit();
    typeLine->setEnabled(false);

    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(typeLine);

    comboSize = new QComboBox();
    comboSize->addItem("1");
    comboSize->addItem("3");
    comboSize->addItem("5");
    //comboSize->addItem("20px");
    comboSize->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    drawButton = new QPushButton();
    drawButton->setText("Draw");

    saveButton = new QPushButton();
    saveButton->setText("Save");

    clearButton = new QPushButton();
    clearButton->setText("Clear");

    QLabel* comboText = new QLabel();
    comboText->setText("Pen width:");

    QHBoxLayout* comboLayout = new QHBoxLayout();
    comboLayout->addWidget(comboText);
    comboLayout->addWidget(comboSize);


    QHBoxLayout* x1Layout = new QHBoxLayout();
    QLabel* x1Label = new QLabel();
    x1Label->setText("x1:");
    x1Layout->addWidget(x1Label);
    x1Layout->addWidget(x1Line);

    QHBoxLayout* y1Layout = new QHBoxLayout();
    QLabel* y1Label = new QLabel();
    y1Label->setText("y1:");
    y1Layout->addWidget(y1Label);
    y1Layout->addWidget(y1Line);


    QHBoxLayout* x2Layout = new QHBoxLayout();
    QLabel* x2Label = new QLabel();
    x2Label->setText("x2:");
    x2Layout->addWidget(x2Label);
    x2Layout->addWidget(x2Line);

    QHBoxLayout* y2Layout = new QHBoxLayout();
    QLabel* y2Label = new QLabel();
    y2Label->setText("y2:");
    y2Layout->addWidget(y2Label);
    y2Layout->addWidget(y2Line);


    QHBoxLayout* x3Layout = new QHBoxLayout();
    QLabel* x3Label = new QLabel();
    x3Label->setText("x3:");
    x3Layout->addWidget(x3Label);
    x3Layout->addWidget(x3Line);

    QHBoxLayout* y3Layout = new QHBoxLayout();
    QLabel* y3Label = new QLabel();
    y3Label->setText("y3:");
    y3Layout->addWidget(y3Label);
    y3Layout->addWidget(y3Line);

    QVBoxLayout* p1Layout = new QVBoxLayout();
    p1Layout->addLayout(x1Layout);
    p1Layout->addLayout(y1Layout);

    QVBoxLayout* p2Layout = new QVBoxLayout();
    p2Layout->addLayout(x2Layout);
    p2Layout->addLayout(y2Layout);

    QVBoxLayout* p3Layout = new QVBoxLayout();
    p3Layout->addLayout(x3Layout);
    p3Layout->addLayout(y3Layout);

    QVBoxLayout* genLayout = new QVBoxLayout();

    genLayout->setSpacing(10);

    genLayout->addLayout(p1Layout);
    genLayout->addLayout(p2Layout);
    genLayout->addLayout(p3Layout);
    genLayout->addWidget(saveButton);
    genLayout->addWidget(listWidget);
    genLayout->addLayout(patternsLayout);
    genLayout->addLayout(comboLayout);
    genLayout->addWidget(drawButton);
    genLayout->addLayout(typeLayout);
    genLayout->addWidget(clearButton);


    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(5);
    mainLayout->addLayout(genLayout);
    mainLayout->addWidget(canvasView);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //QHBoxLayout* genLayout = new QHBoxLayout();

    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(about, &QAction::triggered, this, &MainWindow::showInfo);
    connect(chooseBrushColorAction, &QAction::triggered, this, &MainWindow::chooseColor);
    connect(choosePenColorAction, &QAction::triggered, this, &MainWindow::chooseColor);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveInfo()));
    connect(drawButton, SIGNAL(clicked()), this, SLOT(drawTriangle()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearTriangles()));
    connect(pattern1, SIGNAL(stateChanged(int)), this, SLOT(check()));
    connect(pattern2, SIGNAL(stateChanged(int)), this, SLOT(check()));
    connect(pattern3, SIGNAL(stateChanged(int)), this, SLOT(check()));

}

void MainWindow::showInfo() {

    QString info = "The task is to develop an application for working with graphic primitives (triangles).\n\nMade by Merinov Yaroslav, group 4.";
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText(info);
    msgBox.setWindowIcon(QIcon(":/resource/img/about.png"));
    msgBox.exec();

    //QMessageBox::information(this, "About project", info);

}

void MainWindow::chooseColor() {
    QColor color = QColorDialog::getColor(Qt::gray,this);

    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        if (action == chooseBrushColorAction) {
            brushColor = color;
        } else if (action == choosePenColorAction) {
            penColor = color;
        }
    }
}

void MainWindow::saveInfo() {
    x1 = x1Line->text().toDouble();
    x2 = x2Line->text().toDouble();
    x3 = x3Line->text().toDouble();

    y1 = y1Line->text().toDouble();
    y2 = y2Line->text().toDouble();
    y3 = y3Line->text().toDouble();

    QString coordString = "x1: " + QString::number(x1) + ", y1: " + QString::number(y1) + ", x2: " +
                          QString::number(x2) + ", y2: " + QString::number(y2) + ", x3: " +
                          QString::number(x3) + ", y3: " + QString::number(y3);

    QListWidgetItem *item = new QListWidgetItem(coordString);
    listWidget->addItem(item);



}

void MainWindow::drawTriangle() {

    //qDebug() << "HEllo!";

    QPointF scenePoint1 = canvasView->mapToScene(x1Line->text().toDouble(), y1Line->text().toDouble());
    QPointF scenePoint2 = canvasView->mapToScene(x2Line->text().toDouble(), y2Line->text().toDouble());
    QPointF scenePoint3 = canvasView->mapToScene(x3Line->text().toDouble(), y3Line->text().toDouble());

    QPolygonF trianglePolygon;
    trianglePolygon << scenePoint1 << scenePoint2 << scenePoint3;

    QGraphicsPolygonItem *triangleItem = new QGraphicsPolygonItem(trianglePolygon);

    QPen pen(penColor);
    pen.setWidth(comboSize->currentText().toInt());
    triangleItem->setPen(pen);



    // pattern1->setText("CrossPattern");
    // pattern2->setText("Dense7Pattern");
    // pattern3->setText("HorPattern");

    if (pattern1->isChecked()) {
        QBrush brush(Qt::CrossPattern);
        brush.setColor(brushColor);
        triangleItem->setBrush(brush);

    } else if (pattern2->isChecked()) {
        QBrush brush(Qt::Dense7Pattern);
        brush.setColor(brushColor);
        triangleItem->setBrush(brush);

    } else if (pattern3->isChecked()) {
        QBrush brush(Qt::HorPattern);
        brush.setColor(brushColor);
        triangleItem->setBrush(brush);

    } else {
        QBrush brush(brushColor);
        triangleItem->setBrush(brush);
    }

    canvas->addItem(triangleItem);

    checkTriangleType();
}

void MainWindow::checkTriangleType() {
    double x1 = x1Line->text().toDouble();
    double y1 = y1Line->text().toDouble();
    double x2 = x2Line->text().toDouble();
    double y2 = y2Line->text().toDouble();
    double x3 = x3Line->text().toDouble();
    double y3 = y3Line->text().toDouble();

    double side1 = qSqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2));
    double side2 = qSqrt(qPow(x3 - x2, 2) + qPow(y3 - y2, 2));
    double side3 = qSqrt(qPow(x1 - x3, 2) + qPow(y1 - y3, 2));

    if (side1 + side2 <= side3 || side2 + side3 <= side1 || side1 + side3 <= side2) {
        typeLine->setText("Not a triangle");
        return;
    }

    // double angle1 = qAcos((qPow(side2, 2) + qPow(side3, 2) - qPow(side1, 2)) / (2 * side2 * side3));
    // double angle2 = qAcos((qPow(side1, 2) + qPow(side3, 2) - qPow(side2, 2)) / (2 * side1 * side3));
    // double angle3 = qAcos((qPow(side1, 2) + qPow(side2, 2) - qPow(side3, 2)) / (2 * side1 * side2));

    if (qFuzzyCompare(side1 * side1 + side2 * side2, side3 * side3) || qFuzzyCompare(side2 * side2 + side3 * side3, side1 * side1) || qFuzzyCompare(side1 * side1 + side3 * side3, side2 * side2)){
        typeLine->setText("A right-angled triangle");
    } else if (qFuzzyCompare(side1, side2) && qFuzzyCompare(side2, side3)) {
        typeLine->setText("An equilateral triangle");
    } else if (qFuzzyCompare(side1, side2) || qFuzzyCompare(side2, side3) || qFuzzyCompare(side3, side1)) {
        typeLine->setText("An isosceles triangle");
    } else {
        typeLine->setText("An arbitrary triangle");
    }
}

void MainWindow::clearTriangles() {
    canvas->clear();
    listWidget->clear();
    x1Line->clear();
    x2Line->clear();
    x3Line->clear();
    y1Line->clear();
    y2Line->clear();
    y3Line->clear();
    typeLine->clear();
    pattern1->setChecked(false);
    pattern2->setChecked(false);
    pattern3->setChecked(false);
}

void MainWindow::check() {
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(sender());

    if (checkBox) {
        if (checkBox == pattern1) {
            if (pattern1->isChecked()) {
                pattern2->setEnabled(false);
                pattern3->setEnabled(false);
            } else {
                pattern2->setEnabled(true);
                pattern3->setEnabled(true);
            }
        } else if (checkBox == pattern2) {
            if (pattern2->isChecked()) {
                pattern1->setEnabled(false);
                pattern3->setEnabled(false);
            } else {
                pattern1->setEnabled(true);
                pattern3->setEnabled(true);
            }
        } else if (checkBox == pattern3) {
            if (pattern3->isChecked()) {
                pattern2->setEnabled(false);
                pattern1->setEnabled(false);
            } else {
                pattern2->setEnabled(true);
                pattern1->setEnabled(true);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
