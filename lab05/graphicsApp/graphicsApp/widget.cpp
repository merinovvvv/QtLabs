#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QColor>
#include <QtMath>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QShortcut>
#include <QMouseEvent>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    x_value = std::numeric_limits<double>::quiet_NaN();
    y_value = std::numeric_limits<double>::quiet_NaN();

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

    xValueLine = new QLineEdit();
    yValueLine = new QLineEdit();


    kLine->setEnabled(false);
    aLine->setEnabled(false);
    bLine->setEnabled(false);
    cLine->setEnabled(false);
    dLine->setEnabled(false);
    xValueLine->setEnabled(false);
    yValueLine->setEnabled(false);

    drawButton = new QPushButton();
    clearButton = new QPushButton();
    calcButton = new QPushButton();

    drawButton->setEnabled(false);
    clearButton->setEnabled(false);
    calcButton->setEnabled(false);

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
    QLabel* xValueLabel = new QLabel();
    QLabel* yValueLabel = new QLabel();


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
    xValueLabel->setText("x value:");
    yValueLabel->setText("y value:");


    drawButton->setText("Draw");
    clearButton->setText("Clear");
    calcButton->setText("Calculate");

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

    QHBoxLayout* h12 = new QHBoxLayout();
    h12->addWidget(xValueLabel);
    h12->addWidget(xValueLine);

    QHBoxLayout* h13 = new QHBoxLayout();
    h13->addWidget(yValueLabel);
    h13->addWidget(yValueLine);

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
    settings->addLayout(h12);
    settings->addWidget(calcButton);
    settings->addLayout(h13);
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

    QShortcut *zoomInShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P), this);
    QShortcut *zoomOutShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), this);

    connect (graphChoose, SIGNAL(currentIndexChanged(int)), this, SLOT(graphChanged()));
    connect (colorChoose, SIGNAL(currentIndexChanged(int)), this, SLOT(colorChanged()));
    connect (drawButton, SIGNAL(clicked()), this, SLOT(drawGraph()));
    connect (clearButton, SIGNAL(clicked()), this, SLOT(clearGraph()));
    connect (calcButton, SIGNAL(clicked()), this, SLOT(calcValue()));

    connect(zoomInShortcut, SIGNAL(activated()), this, SLOT(zoomIn()));
    connect(zoomOutShortcut, SIGNAL(activated()), this, SLOT(zoomOut()));
}

void Widget::drawCoordinatePlane(QGraphicsScene* scene) {
    scene->clear();

    qreal sceneWidth = scene->width();
    qreal sceneHeight = scene->height();

    QRectF sceneRect = scene->sceneRect();
    QPointF topLeftCorner = sceneRect.topLeft();

    // adding horizontal lines below center
    for (qreal y = sceneHeight/2; y <= sceneHeight; y += step) {
        scene->addLine(topLeftCorner.x(), y, sceneWidth, y, QPen(Qt::gray));
    }

    // adding horizontal lines above center
    for (qreal y =  sceneHeight/2; y >= topLeftCorner.y(); y -= step) {
        scene->addLine(topLeftCorner.x(), y, sceneWidth, y, QPen(Qt::gray));
    }


    // adding vertical lines on the right
    for (qreal x = sceneWidth/2; x <= sceneWidth; x += step) {
        scene->addLine(x, topLeftCorner.y(), x, sceneHeight, QPen(Qt::gray));
    }

    // adding vertical lines on the left
    for (qreal x = sceneWidth/2; x >= topLeftCorner.x(); x -= step) {
        scene->addLine(x, topLeftCorner.y(), x, sceneHeight, QPen(Qt::gray));
    }

    // adding axes
    scene->addLine(topLeftCorner.x(), sceneHeight/2, sceneWidth, sceneHeight/2, QPen(Qt::black, 2)); // horizontal
    scene->addLine(sceneWidth/2, topLeftCorner.y(), sceneWidth/2, sceneHeight, QPen(Qt::black, 2)); // vertical

    //qDebug() << sceneWidth/2;


    QTransform transform;
    transform.translate(sceneWidth / 2, sceneHeight / 2);
    transform.scale(1, -1);

    // labels on the Ox on the right
    for (qreal x = 0, i = 0; x <= sceneWidth / 2; x += step, ++i) {
        if (x != 0) {
            QPointF labelPos = transform.map(QPointF(x, 0));
            QGraphicsTextItem* textItem = scene->addText(QString::number(i), QFont("Arial", 6));
            textItem->setPos(labelPos);
        }
    }

    // labels on the Ox on the left
    for (qreal x = -step, i = -1; x >= -sceneWidth / 2; x -= step, --i) {
        QPointF labelPos = transform.map(QPointF(x, 0));
        QGraphicsTextItem* textItem = scene->addText(QString::number(i), QFont("Arial", 6));
        textItem->setPos(labelPos);
    }

    // labels on the Oy above the center
    for (qreal y = step, i = 1; y <= sceneHeight / 2; y += step, ++i) {
        QPointF labelPos = transform.map(QPointF(0, y));
        QGraphicsTextItem* textItem = scene->addText(QString::number(i), QFont("Arial", 6));
        textItem->setPos(labelPos);
    }

    // labels on the Oy below the center
    for (qreal y = -step, i = -1; y >= -sceneHeight / 2; y -= step, --i) {
        QPointF labelPos = transform.map(QPointF(0, y));
        QGraphicsTextItem* textItem = scene->addText(QString::number(i), QFont("Arial", 6));
        textItem->setPos(labelPos);
    }

    //zero label
    QPointF zeroLabelPos = transform.map(QPointF(0, 0));
    QGraphicsTextItem* textItem = scene->addText(QString::number(0), QFont("Arial", 6));
    textItem->setPos(zeroLabelPos);


    //arrows on the ends of axes
    qreal arrowSize = 10;
    QPolygonF arrowHead;
    arrowHead << QPointF(0, 0) << QPointF(-arrowSize / 2, -arrowSize) << QPointF(arrowSize / 2, -arrowSize);

    QPointF arrowXPos = transform.map(QPointF(sceneWidth/2, 0));
    QPointF arrowYPos = transform.map(QPointF(0, sceneHeight/2));


    // Ox arrow
    QGraphicsPolygonItem* xArrowPositive = scene->addPolygon(arrowHead, QPen(Qt::black), QBrush(Qt::black));


    xArrowPositive->setPos(arrowXPos.x(), arrowXPos.y());
    xArrowPositive->setRotation(-90);

    // Oy arrow
    QGraphicsPolygonItem* yArrowPositive = scene->addPolygon(arrowHead, QPen(Qt::black), QBrush(Qt::black));
    yArrowPositive->setPos(arrowYPos.x(), arrowYPos.y());
    yArrowPositive->setRotation(180);

}


void Widget::graphChanged() {

    if (graphChoose->currentText() != "") {
        drawButton->setEnabled(true);
        calcButton->setEnabled(true);
        xValueLine->setEnabled(true);
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

    // for (QGraphicsLineItem* line : lines) {
    //     graphSurface->removeItem(line);
    //     delete line;
    // }
    // lines.clear();

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

                QGraphicsLineItem* lineItem = graphSurface->addLine(QLineF(previousPoint, scenePoint), pen);
                lines.append(lineItem);

                //graphSurface->addLine(QLineF(previousPoint, scenePoint), pen);
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
    xValueLine->clear();
    yValueLine->clear();

    //calcButton->setEnabled(false);

    for (QGraphicsLineItem* line : lines) {
        graphSurface->removeItem(line);
        delete line;
    }
    lines.clear();

    //graphSurface->clear();
    drawCoordinatePlane(graphSurface);
    clearButton->setEnabled(false);

    x_value = std::numeric_limits<double>::quiet_NaN();
    y_value = std::numeric_limits<double>::quiet_NaN();
}

void Widget::calcValue() {

    if (xMinLine->text().isEmpty() || xMaxLine->text().isEmpty() || yMinLine->text().isEmpty() || yMaxLine->text().isEmpty()) {
        return;
    }

    x_value = xValueLine->text().toDouble();

    if (graphChoose->currentText() == linear) {
        y_value = k_ * x_value + b_;
    } else if (graphChoose->currentText() == quadro) {
        y_value = a_ * x_value * x_value + b_ * x_value + c_;
    } else if (graphChoose->currentText() == cubic) {
        y_value = a_ * x_value * x_value * x_value + b_ * x_value * x_value + c_ * x_value + d_;
    } else if (graphChoose->currentText() == cubic) {
        qreal x_value_tmp = x_value;
        for (size_t i = 0; i < b_; ++i) {
            x_value_tmp *= x_value;
        }
        y_value = a_ * x_value_tmp + qSin(c_ * x_value);
    } else {
        y_value = std::numeric_limits<double>::quiet_NaN();
    }

    yValueLine->setText(QString::number(y_value));
}

void Widget::zoomIn() { //TODO

    for (QGraphicsLineItem* line : lines) {
        graphSurface->removeItem(line);
        delete line;
    }
    lines.clear();

    step *= 1.2;
    drawCoordinatePlane(graphSurface);
    drawGraph();
}

void Widget::zoomOut() {

    for (QGraphicsLineItem* line : lines) {
        graphSurface->removeItem(line);
        delete line;
    }
    lines.clear();

    step /= 1.2;
    drawCoordinatePlane(graphSurface);
    drawGraph();
}

void Widget::mousePressEvent(QMouseEvent* event) {

    qreal sceneWidth = graphSurface->width();
    qreal sceneHeight = graphSurface->height();

    //QRectF sceneRect = graphSurface->sceneRect();
    //QPointF topLeftCorner = sceneRect.topLeft();

    qreal sceneCenterX = sceneWidth / 2;
    qreal sceneCenterY = sceneHeight / 2;

    QPoint centerPoint = graphShow->mapToParent(QPoint(sceneCenterX, sceneCenterY));
    //qDebug() << centerPoint.x() << " " << centerPoint.y();

    // QTransform transform;
    // transform.translate(-sceneCenterX, -sceneCenterY);
    // //transform.scale(1, -1);

    // QPointF transformedPoint = transform.map(QPointF(sceneCenterX, sceneCenterY));
    // qDebug() << "Transformed Point: " << transformedPoint.x() << " " << transformedPoint.y();


    QPoint topLeftCorner = graphShow->mapToParent(QPoint(0, 0));// We get the coordinates of the upper-left corner of the scene in the widget system
    QPoint bottomRightCorner = graphShow->mapToParent(QPoint(graphShow->width(), graphShow->height())); // We get the coordinates of the bottom right corner of the scene in the widget system

    qDebug() << topLeftCorner.x() << " " << topLeftCorner.y();

    QPoint cursorClick = event->pos();
    qDebug() << cursorClick.x() << " " << cursorClick.y();

    if (cursorClick.x() < topLeftCorner.x() || cursorClick.y() < topLeftCorner.y() || cursorClick.x() > bottomRightCorner.x() || cursorClick.y() > bottomRightCorner.y()) {
        return;
    }

    qreal distanceToPoint = cursorClick.x() - topLeftCorner.x();
    qreal distanceToCenter = centerPoint.x() - topLeftCorner.x();
    qreal distance = distanceToCenter - distanceToPoint;

    qreal x;

    x = -1 * distance / step;
    x_value = x;

    if (lines.isEmpty()) {
        xValueLine->setText(QString("%1").arg(x));
        y_value = std::numeric_limits<double>::quiet_NaN();
        yValueLine->setText(QString("%1").arg(y_value));
        return;
    }

    // Calculate y based on the selected graph type and the x value
    QString selectedGraph = graphChoose->currentText();
    if (selectedGraph == linear) {
        y_value = k_ * x + b_;
    } else if (selectedGraph == quadro) {
        y_value = a_ * x * x + b_ * x + c_;
    } else if (selectedGraph == cubic) {
        y_value = a_ * x * x * x + b_ * x * x + c_ * x + d_;
    } else if (selectedGraph == random) {
        y_value = a_ * pow(x, b_) + sin(c_ * x);
    }

    // Display the calculated y value in yValueLine
    yValueLine->setText(QString("%1").arg(y_value));

    // Display the x value in xValueLine
    xValueLine->setText(QString("%1").arg(x));
}


Widget::~Widget()
{
    delete ui;
}
