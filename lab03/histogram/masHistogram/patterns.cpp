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

    int x = 10; //the start horizontal position
    int rectWidth = (width() - 10 * (numbers.size() - 1)) / numbers.size(); // the width of rectangle

    int maxRectHeight = height() - 20;
    int yBottom = height() - 10; // The y coordinate for the lower boundary of the rendering area

    int rectHeight;
    int yTop; //the 2nd coordinate of rectangle

    for (size_t i = 0; i < numbers.size(); ++i) {

        rectHeight = numbers[i] * maxRectHeight / 50; //50 is the max value of numbers[i]
        yTop = yBottom - rectHeight;

        painter.setBrush(patterns[i % patterns.size()]);
        painter.drawRect(x, yTop, rectWidth, rectHeight);
        x += rectWidth + 10;
    }
}
