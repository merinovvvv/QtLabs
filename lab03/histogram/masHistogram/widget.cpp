#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    valueList.push_back(1);
    valueList.push_back(10);
    valueList.push_back(5);
    valueList.push_back(20);
    valueList.push_back(30);
    valueList.push_back(35);
    valueList.push_back(45);
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    QPainter qp(this);
    drawHistogram(&qp);
}

void Widget::drawHistogram(QPainter *qp) {

    QRect rect(100, 100, 50, 200);
    qp->fillRect(rect, Qt::blue);
    QPen pen(Qt::black, 2, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(20, 40, 250, 40);

    pen.setStyle(Qt::DashLine);
    qp->setPen(pen);
    qp->drawLine(20, 80, 250, 80);

    pen.setStyle(Qt::DashDotLine);
    qp->setPen(pen);
    qp->drawLine(20, 120, 250, 120);

    pen.setStyle(Qt::DotLine);
    qp->setPen(pen);
    qp->drawLine(20, 160, 250, 160);

    pen.setStyle(Qt::DashDotDotLine);
    qp->setPen(pen);
    qp->drawLine(20, 200, 250, 200);

    QVector<qreal> dashes;
    qreal space = 4;

    dashes << 1 << space << 5 << space;

    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);

    qp->setPen(pen);
    qp->drawLine(20, 240, 250, 240);
}
