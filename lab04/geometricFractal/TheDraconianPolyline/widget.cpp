#include <QPainter>
#include <QMouseEvent>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setFixedSize(800, 600);
    //setWindowTitle("Dragon Curve in Qt C++");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    QString axiom = "FX";
    QString tempAx = "";
    QMap<QChar, QString> logic = {{'X', "X+YF+"}, {'Y', "-FX-Y"}};
    int count = 15;

    for (int i = 0; i < count; ++i) {
        for (QChar j : axiom) {
            tempAx += logic.contains(j) ? logic[j] : QString(j);
        }
        axiom = tempAx;
        tempAx.clear();
    }

    QColor color;

    for (QChar k : axiom) {
        if (k == 'F') {
            color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
            painter.setPen(color);
            painter.translate(0, -2.5);
            painter.drawLine(0, 0, 0, -2.5);
        } else if (k == '+') {
            painter.rotate(-90);
        } else if (k == '-') {
            painter.rotate(90);
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        this->close();
    }
}
