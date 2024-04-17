#include <QtMath>
#include <QColor>
#include <QPainter>
#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    int width_ = width();
    int height_ = height();

    int n = qCeil(std::log2f(qMax(width_, height_) - 1));
    dots_ = qPow(2, n) + 1;

    plazma_.resize(dots_);

    for (auto &i : plazma_) {
        i.resize(dots_);
        for (auto & item: i) {
            item = nullptr;
        }
    }

    dotsColorInit();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dotsColorInit() {

    //Шаг 1. Инициализация угловых точек. Присваивание им значений высот (например, выбором случайных чисел).
    plazma_[0][0] = QColor(Qt::red);
    plazma_[0][dots_ - 1] = QColor(Qt::green);
    plazma_[dots_ - 1][0] = QColor(Qt::blue);
    plazma_[dots_ - 1][dots_ - 1] = QColor(Qt::yellow);

    int x1 = 0;
    int y1 = 0;
    int x2 = dots_ - 1;
    int y2 = dots_ - 1;

    fillPlazma (x1, y1, x2, y2);
    update();
}

void Widget::fillPlazma (int& x1, int& y1, int& x2, int& y2) {

    if (x2 - x1 <= 1 && y2 - y1 <= 1)
        return; // Базовый случай: если размер области слишком мал, выходим из рекурсии


    //Шаг 2. Шаг diamond. Нахождение срединной точки, присваивание ей значения, на основе среднего от угловых, плюс случайное число

    int xCenter = (x1 + x2) / 2;
    int yCenter = (y1 + y2) / 2;
    int redCenter = (plazma_[x1][y1].red() + plazma_[x1][y2].red() + plazma_[x2][y1].red() + plazma_[x2][y2].red()) / 4;

    int greenCenter = (plazma_[x1][y1].green() + plazma_[x1][y2].green() + plazma_[x2][y1].green() + plazma_[x2][y2].green()) / 4;

    int blueCenter = (plazma_[x1][y1].blue() + plazma_[x1][y2].blue() + plazma_[x2][y1].blue() + plazma_[x2][y2].blue()) / 4;

    redCenter = qFabs((QRandomGenerator::global()->bounded(-delta,delta) + redCenter) % 256);

    greenCenter = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + greenCenter) % 256);

    blueCenter = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + blueCenter) % 256);

    QColor colorCenter = QColor(redCenter, greenCenter, blueCenter);

    plazma_[xCenter][yCenter] = colorCenter;

    //Шаг 3. Шаг square. Нахождение срединных точек для ромбов отмеченных черными точками (на этом шаге, по одной точке каждого ромба выходят за пределы массива). Плюс случайное число.

    int xLeft = x1;
    int yLeft = yCenter;
    int xRight = x2;
    int yRight = yCenter;
    int xBottom = xCenter;
    int yBottom  = y1; //it is top actually
    int xTop = xCenter;
    int yTop = y2; //it is bottom actually


    //find the color of the left point


    int redLeft = (plazma_[x1][y1].red() + plazma_[x1][y2].red() + plazma_[xCenter][yCenter].red());
    int greenLeft = (plazma_[x1][y1].green() + plazma_[x1][y2].green() + plazma_[xCenter][yCenter].green());
    int blueLeft = (plazma_[x1][y1].blue() + plazma_[x1][y2].blue() + plazma_[xCenter][yCenter].blue());
    int xLeftLeft = 2 * x1 - xCenter; //x1 - (xCenter - x1)

    if(xLeftLeft >= 0){
        redLeft += plazma_[xLeftLeft][yCenter].red();
        redLeft /= 4;
        greenLeft += plazma_[xLeftLeft][yCenter].red();
        greenLeft /= 4;
        blueLeft += plazma_[xLeftLeft][yCenter].red();
        blueLeft /= 4;
    }else {
        redLeft /=3;
        greenLeft /=3;
        blueLeft /=3;
    }


    redLeft = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + redLeft) % 256);

    greenLeft = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + greenLeft) % 256);

    blueLeft = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + blueLeft) % 256);

    QColor colorLeft = QColor(redLeft, greenLeft, blueLeft);

    plazma_[xLeft][yLeft] = colorLeft;

    //find the color of the right point

    int redRight = (plazma_[x2][y1].red() + plazma_[x2][y2].red() + plazma_[xCenter][yCenter].red());
    int greenRight= (plazma_[x2][y1].green() + plazma_[x2][y2].green() + plazma_[xCenter][yCenter].green());
    int blueRight = (plazma_[x2][y1].blue() + plazma_[x2][y2].blue() + plazma_[xCenter][yCenter].blue());

    int xRightRight = 2 * x2 - xCenter; //x2 + (x2 - xCenter)
    if(xRightRight < dots_){
        redRight += plazma_[xRightRight][yCenter].red();
        redRight /= 4;
        greenRight += plazma_[xRightRight][yCenter].green();
        greenRight /= 4;
        blueRight += plazma_[xRightRight][yCenter].blue();
        blueRight /= 4;
    }else {
        redRight /=3;
        greenRight /=3;
        blueRight /=3;
    }


    redRight = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + redRight) % 256);

    greenRight = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + greenRight) % 256);

    blueRight = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + blueRight) % 256);

    QColor colorRight = QColor(redRight, greenRight, blueRight);

    plazma_[xRight][yRight] = colorRight;

    //find the color of the top point

    int redTop = (plazma_[x1][y2].red() + plazma_[x2][y2].red() + plazma_[xCenter][yCenter].red());
    int greenTop = (plazma_[x1][y2].green() + plazma_[x2][y2].green() + plazma_[xCenter][yCenter].green());
    int blueTop = (plazma_[x1][y2].blue() + plazma_[x2][y2].blue() + plazma_[xCenter][yCenter].blue());

    int yTopTop = 2 * y2 - yCenter; //y2 + (y2 - yCenter)
    if(yTopTop < dots_){
        redTop += plazma_[xCenter][yTopTop].red();
        redTop /= 4;
        greenTop += plazma_[xCenter][yTopTop].green();
        greenTop /= 4;
        blueTop += plazma_[xCenter][yTopTop].blue();
        blueTop /= 4;
    }else {
        redTop /=3;
        greenTop /=3;
        blueTop /=3;
    }

    redTop = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + redTop) % 256);

    greenTop = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + greenTop) % 256);

    blueTop = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + blueTop) % 256);

    QColor colorTop = QColor(redTop, greenTop, blueTop);

    plazma_[xTop][yTop] = colorTop;


//find the color of the bottom point

    int redBottom = (plazma_[x1][y1].red() + plazma_[x2][y1].red() + plazma_[xCenter][yCenter].red());
    int greenBottom = (plazma_[x1][y1].green() + plazma_[x2][y1].green() + plazma_[xCenter][yCenter].green());
    int blueBottom = (plazma_[x1][y1].blue() + plazma_[x2][y1].blue() + plazma_[xCenter][yCenter].blue());

    int yBottomBottom = 2 * y1 - yCenter; //y1 - (yCenter - y1)
    if(yBottomBottom > 0){
        redBottom += plazma_[xCenter][yBottomBottom].red();
        redBottom /= 4;
        greenBottom += plazma_[xCenter][yBottomBottom].green();
        greenBottom /= 4;
        blueBottom += plazma_[xCenter][yBottomBottom].blue();
        blueBottom /= 4;
    }else {
        redBottom /=3;
        greenBottom /=3;
        blueBottom /=3;
    }

    redBottom = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + redBottom) % 256);

    greenBottom = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + greenBottom) % 256);

    blueBottom = qFabs((QRandomGenerator::global()->bounded(-delta, delta) + blueBottom) % 256);

    QColor colorBottom = QColor(redBottom, greenBottom, blueBottom);

    plazma_[xBottom][yBottom] = colorBottom;


    fillPlazma(x1, y1, xCenter, yCenter);
    fillPlazma(xCenter, y1, x2, yCenter);
    fillPlazma(x1, yCenter, xCenter, y2);
    fillPlazma(xCenter, yCenter, x2, y2);

}

void Widget::paintEvent (QPaintEvent *qp) {
    Q_UNUSED (qp)


    QPainter painter(this);

    for (int i = 0; i < height(); ++i){
        for (int j = 0; j < width(); ++j) {
            painter.fillRect(i, j, 1, 1, plazma_[i][j]);
        }
    }
}

