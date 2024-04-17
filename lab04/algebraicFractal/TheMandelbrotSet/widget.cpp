#include <QPainter>
#include <complex>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(800, 800);
    setWindowTitle("The Mandelbrot Set");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent (QPaintEvent *event) {

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const std::complex<double> focus(-0.7, 0.0);
    const double zoom = 3.0;
    const int maxIter = 1000;

    for (int px = 0; px < width(); ++px) {
        for (int py = 0; py < height(); ++py) {
            std::complex<double> point((double)px / width() - 0.5, (double)py / height() - 0.5);
            point *= zoom;
            point += focus;
            std::complex<double> z(0.0, 0.0);
            int iter = 0;
            while (abs(z) < 2.0 && iter < maxIter) {
                z = z * z + point;
                ++iter;
            }
            if (iter < maxIter) {
                double log_zn = log(z.real() * z.real() + z.imag() * z.imag()) / 2; //Это вычисление логарифма модуля квадрата комплексного числа z. Это делается для того, чтобы учесть скорость ухода точки в бесконечность.
                double nu = log(log_zn / log(2)) / log(2); //Это вычисление так называемого “гладкого” значения итерации. Это делается для того, чтобы сгладить цвета между различными итерациями и получить более детализированное изображение фрактала.
                iter = iter + 1 - nu;
                QColor color = QColor::fromHsv(255 * iter / maxIter, 255, 255 * (iter < maxIter));
                painter.setPen(color);
                painter.drawPoint(px, py);
            } else {
                painter.setPen(Qt::black);
                painter.drawPoint(px, py);
            }
        }
    }
}
