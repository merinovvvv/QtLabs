#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QColor>
#include <QtMath>
#include <QDebug>
#include <QGraphicsTextItem>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    color = Qt::red;

    QVBoxLayout* settings = new QVBoxLayout();

    graphChoose = new QComboBox();
    colorChoose = new QComboBox();

    graphChoose->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    colorChoose->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    xMinLine = new QLineEdit();
    xMaxLine = new QLineEdit();
    yMinLine = new QLineEdit();
    yMaxLine = new QLineEdit();

    xMinLine->setEnabled(false);
    xMaxLine->setEnabled(false);
    yMinLine->setEnabled(false);
    yMaxLine->setEnabled(false);

    kLine = new QLineEdit();
    aLine = new QLineEdit();
    bLine = new QLineEdit();
    cLine = new QLineEdit();
    dLine = new QLineEdit();

    kLine->setEnabled(false);
    aLine->setEnabled(false);
    bLine->setEnabled(false);
    cLine->setEnabled(false);
    dLine->setEnabled(false);

    drawButton = new QPushButton();
    clearButton = new QPushButton();

    drawButton->setEnabled(false);
    clearButton->setEnabled(false);

    QLabel* graphLabel = new QLabel();
    QLabel* colorLabel = new QLabel();
    QLabel* xMinLabel = new QLabel();
    QLabel* xMaxLabel = new QLabel();
    QLabel* yMinLabel = new QLabel();
    QLabel* yMaxLabel = new QLabel();

    QLabel* kLabel = new QLabel();
    QLabel* aLabel = new QLabel();
    QLabel* bLabel = new QLabel();
    QLabel* cLabel = new QLabel();
    QLabel* dLabel = new QLabel();


    graphChoose->addItem("");
    graphChoose->addItem(linear);
    graphChoose->addItem(quadro);
    graphChoose->addItem(cubic);
    graphChoose->addItem(random);

    colorChoose->addItem("red");
    colorChoose->addItem("green");
    colorChoose->addItem("blue");

    graphLabel->setText("function:");
    colorLabel->setText("color:");

    xMinLabel->setText("x_min:");
    xMaxLabel->setText("x_max:");
    yMinLabel->setText("y_min:");
    yMaxLabel->setText("y_max:");

    kLabel->setText("k:");
    aLabel->setText("a:");
    bLabel->setText("b:");
    cLabel->setText("c:");
    dLabel->setText("d:");

    drawButton->setText("Draw");
    clearButton->setText("Clear");

    QHBoxLayout* h1 = new QHBoxLayout();
    h1->addWidget(graphLabel);
    h1->addWidget(graphChoose);
    //h1->setAlignment(Qt::AlignLeft);

    QHBoxLayout* h2 = new QHBoxLayout();
    h2->addWidget(colorLabel);
    h2->addWidget(colorChoose);
    //h2->setAlignment(Qt::AlignLeft);

    QHBoxLayout* h3 = new QHBoxLayout();
    h3->addWidget(xMinLabel);
    h3->addWidget(xMinLine);

    QHBoxLayout* h4 = new QHBoxLayout();
    h4->addWidget(xMaxLabel);
    h4->addWidget(xMaxLine);

    QHBoxLayout* h5 = new QHBoxLayout();
    h5->addWidget(yMinLabel);
    h5->addWidget(yMinLine);

    QHBoxLayout* h6 = new QHBoxLayout();
    h6->addWidget(yMaxLabel);
    h6->addWidget(yMaxLine);

    QHBoxLayout* h7 = new QHBoxLayout();
    h7->addWidget(kLabel);
    h7->addWidget(kLine);

    QHBoxLayout* h8 = new QHBoxLayout();
    h8->addWidget(aLabel);
    h8->addWidget(aLine);

    QHBoxLayout* h9 = new QHBoxLayout();
    h9->addWidget(bLabel);
    h9->addWidget(bLine);

    QHBoxLayout* h10 = new QHBoxLayout();
    h10->addWidget(cLabel);
    h10->addWidget(cLine);

    QHBoxLayout* h11 = new QHBoxLayout();
    h11->addWidget(dLabel);
    h11->addWidget(dLine);


    settings->addLayout(h1);
    settings->addLayout(h2);
    settings->addLayout(h3);
    settings->addLayout(h4);
    settings->addLayout(h5);
    settings->addLayout(h6);
    settings->addLayout(h7);
    settings->addLayout(h8);
    settings->addLayout(h9);
    settings->addLayout(h10);
    settings->addLayout(h11);
    settings->addWidget(drawButton);
    settings->addWidget(clearButton);

    graphSurface = new QGraphicsScene();
    graphShow = new QGraphicsView();

    graphSurface->setSceneRect(0, 0, 860, 760);

    //graphShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    graphShow->setScene(graphSurface);
    //graphShow->setGeometry(0, 0, 865, 765);
    drawCoordinatePlane(graphSurface);


    QHBoxLayout* generalLayout = new QHBoxLayout();
    generalLayout->addLayout(settings);
    generalLayout->addWidget(graphShow);

    setLayout(generalLayout);

    connect (graphChoose, SIGNAL(currentIndexChanged(int)), this, SLOT(graphChanged()));
    connect (colorChoose, SIGNAL(currentIndexChanged(int)), this, SLOT(colorChanged()));
    connect (drawButton, SIGNAL(clicked()), this, SLOT(drawGraph()));
    connect (clearButton, SIGNAL(clicked()), this, SLOT(clearGraph()));
}

void Widget::drawCoordinatePlane(QGraphicsScene* scene) {
    qreal sceneWidth = scene->width();
    qreal sceneHeight = scene->height();


    // adding horizontal lines on coordinate plane
    for (qreal y = 0; y <= sceneHeight; y += step) {
        scene->addLine(0, y, sceneWidth, y, QPen(Qt::gray));

        //QGraphicsTextItem* textItem = scene->addText(QString::number(sceneHeight / 2 - y), QFont("Arial", 6)); // Маленький размер шрифта
        //textItem->setPos(sceneWidth / 2 - 30, y - 5); // Положение текста (слева от оси X)
    }

     // adding vertical lines on coordinate plane
    for (qreal x = 0; x <= sceneWidth; x += step) {
        scene->addLine(x, 0, x, sceneHeight, QPen(Qt::gray));

        //QGraphicsTextItem* textItem = scene->addText(QString::number(x - sceneWidth / 2), QFont("Arial", 6)); // Маленький размер шрифта
        //textItem->setPos(x - 10, sceneHeight / 2 + 5); // Положение текста (под осью Y)
    }

    // adding coordinate axes
    scene->addLine(0, sceneHeight / 2, sceneWidth, sceneHeight / 2, QPen(Qt::black, 2)); // Горизонтальная ось
    scene->addLine(sceneWidth / 2, 0, sceneWidth / 2, sceneHeight, QPen(Qt::black, 2)); // Вертикальная ось
}

void Widget::graphChanged() {

    if (graphChoose->currentText() != "") {
        drawButton->setEnabled(true);
    }

    xMinLine->setEnabled(true);
    xMaxLine->setEnabled(true);
    yMinLine->setEnabled(true);
    yMaxLine->setEnabled(true);
    if (graphChoose->currentText() == linear) {
        aLine->setEnabled(false);
        bLine->setEnabled(true);
        cLine->setEnabled(false);
        dLine->setEnabled(false);
        kLine->setEnabled(true);
    } else if (graphChoose->currentText() == quadro || graphChoose->currentText() == random || graphChoose->currentText() == cubic) {
        kLine->setEnabled(false);
        aLine->setEnabled(true);
        bLine->setEnabled(true);
        cLine->setEnabled(true);
        if (graphChoose->currentText() == cubic) {
            dLine->setEnabled(true);
        } else {
            dLine->setEnabled(false);
        }
    } else {
        drawButton->setEnabled(false);
        xMinLine->setEnabled(false);
        xMaxLine->setEnabled(false);
        yMinLine->setEnabled(false);
        yMaxLine->setEnabled(false);
        aLine->setEnabled(false);
        bLine->setEnabled(false);
        cLine->setEnabled(false);
        dLine->setEnabled(false);
        kLine->setEnabled(false);
    }
}

void Widget::colorChanged() {
    color = QColor(colorChoose->currentText());
    //qDebug() << color.name();
}

void Widget::drawGraph() {

    QTransform transform;
    transform.translate(graphSurface->width()/2, graphSurface->height()/2);
    transform.scale(step, -step);

    clearButton->setEnabled(true);

    x_min_ = xMinLine->text().toDouble();
    x_max_ = xMaxLine->text().toDouble();
    y_min_ = yMinLine->text().toDouble();
    y_max_ = yMaxLine->text().toDouble();

    k_ = kLine->text().toDouble();
    a_ = aLine->text().toDouble();
    b_ = bLine->text().toDouble();
    c_ = cLine->text().toDouble();
    d_ = dLine->text().toDouble();

    //graphSurface->clear();

    QString selectedGraph = graphChoose->currentText();

    // Creating an array to store graph points
    QVector<QPointF> points;

    // Calculating and adding graph points to an array
    qreal step = 0.1;
    for (qreal x = x_min_; x <= x_max_; x += step) {
        qreal y = 0;
        if (selectedGraph == linear) {
            y = k_ * x + b_; // y = kx + b
        } else if (selectedGraph == quadro) {
            y = a_ * x * x + b_ * x + c_; // y = ax^2 + bx + c
        } else if (selectedGraph == cubic) {
            y = a_ * x * x * x + b_ * x * x + c_ * x + d_; // y = ax^3 + bx^2 + cx + d
        } else if (selectedGraph == random) {
            y = a_ * pow(x, b_) + sin(c_ * x); // у = ax^b + sin(cx)
        }

        QPointF p = transform.map(QPointF(x, y));
        points.append(p);
    }

        QPointF previousPoint;
        for (const QPointF& point : points) {
            QPointF scenePoint(point.x(), point.y());

            if (!previousPoint.isNull()) {
                QPen pen(color);
                qDebug() << color.name();
                graphSurface->addLine(QLineF(previousPoint, scenePoint), pen);
            }
            previousPoint = scenePoint;
        }
}

void Widget::clearGraph() {
    xMinLine->clear();
    xMaxLine->clear();
    yMinLine->clear();
    yMaxLine->clear();
    kLine->clear();
    aLine->clear();
    bLine->clear();
    cLine->clear();
    dLine->clear();
    graphSurface->clear();
    drawCoordinatePlane(graphSurface);
    clearButton->setEnabled(false);
}


Widget::~Widget()
{
    delete ui;
}
