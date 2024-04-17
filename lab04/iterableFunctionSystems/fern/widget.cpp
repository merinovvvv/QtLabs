#include <QPainter>
#include <QTime>
#include <QMouseEvent>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setFixedSize(800, 1000);
    //setWindowTitle("Barnsley Fern in Qt C++");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent (QPaintEvent *qp) {

    Q_UNUSED(qp);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::black);

    double x = 0, y = 0;
    int width = this->width();
    int height = this->height();
    double scale = 90;  // Подберите этот параметр экспериментально

    for (int i = 0; i < 100000; ++i) {
        painter.setPen(Qt::green);
        painter.drawPoint(width / 2 + x * scale, height - y * scale);

        double nextX, nextY;
        int r = rand() % 100;
        if (r < 1) {
            nextX = 0;
            nextY = 0.16 * y;
        } else if (r < 86) {
            nextX = 0.85 * x + 0.04 * y;
            nextY = -0.04 * x + 0.85 * y + 1.6;
        } else if (r < 93) {
            nextX = 0.2 * x - 0.26 * y;
            nextY = 0.23 * x + 0.22 * y + 1.6;
        } else {
            nextX = -0.15 * x + 0.28 * y;
            nextY = 0.26 * x + 0.24 * y + 0.44;
        }
        x = nextX;
        y = nextY;
    }
}

void Widget::mousePressEvent (QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->close();
    }
}
