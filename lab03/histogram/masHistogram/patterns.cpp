#include <QTextStream>
#include <QPainter>
#include <QRandomGenerator>

#include "patterns.h"
#include "ui_patterns.h"

Patterns::Patterns(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Patterns)
{
    ui->setupUi(this);
    masItemsGen(numbers);
}

Patterns::~Patterns()
{
    delete ui;
}

void Patterns::masItemsGen(QVector <qint64> &numbers) {

    size_t arrSize = QRandomGenerator::global()->bounded(1, 20);

    for (size_t i = 0; i < arrSize; ++i) {
        numbers.push_back(QRandomGenerator::global()->bounded(1, 50));
    }

}

void Patterns::paintEvent (QPaintEvent *pe) {
    Q_UNUSED(pe);

    doPainting();
}

void Patterns::doPainting() {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    //int x = 0; //the start horizontal position
    int rectWidth = width() / numbers.size(); // the width of rectangle

    int maxRectHeight = height() - 20;
    int yBottom = height(); // The y coordinate for the lower boundary of the rendering area

    int rectHeight;
    int yTop; //the 2nd coordinate of rectangle

    for (size_t i = 0; i < numbers.size(); ++i) {

        rectHeight = numbers[i] * maxRectHeight / 50; //50 is the max value of numbers[i]
        yTop = yBottom - rectHeight;

        // Generate random color
        QColor randomColor = QColor::fromRgb(qrand() % 256, qrand() % 256, qrand() % 256);

        // Set brush to random color
        painter.setBrush(randomColor);


        if (width() % numbers.size() != 0) {
            rectWidth++;
        }

        // Draw rectangle with random color
        painter.drawRect(i * rectWidth, yTop, rectWidth, rectHeight);

        // Set pattern for filling
        painter.setBrush(patterns[i % patterns.size()]);

        // Draw pattern over the rectangle
        painter.drawRect(i * rectWidth, yTop, rectWidth, rectHeight);

        if (width() % numbers.size() != 0) {
            rectWidth--;
        }

        //x += rectWidth;
    }
}

