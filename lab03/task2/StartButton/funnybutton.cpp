#include "funnybutton.h"
#include "ui_funnybutton.h"
#include <QEvent>
#include <QMouseEvent>
#include <QRandomGenerator>


FunnyButton::FunnyButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FunnyButton)
{
    ui->setupUi(this);
    ui->pushButton->setFixedSize(100, 100);
    //this->setFixedSize(1920, 1080);
    setMouseTracking(true);
}

FunnyButton::~FunnyButton()
{
    delete ui;
}

QColor FunnyButton::GenerateRandomColor() {
    QRandomGenerator rand(QRandomGenerator::global()->generate());
    int red = rand.bounded(256);
    int green = rand.bounded(256);
    int blue = rand.bounded(256);

    return QColor(red, green, blue);
}

void FunnyButton::on_pushButton_clicked()
{
    QColor randomColor = GenerateRandomColor();
    ui->pushButton->setStyleSheet(QString("background-color: %1").arg(randomColor.name()));
}

void FunnyButton::mouseMoveEvent(QMouseEvent *event) {

    if (ui->pushButton->underMouse()) {

        int widgetWidth = this->width();
        int widgetHeight = this->height();


        int newX = QRandomGenerator::global()->bounded(widgetWidth - ui->pushButton->width());
        int newY = QRandomGenerator::global()->bounded(widgetHeight - ui->pushButton->height());

        ui->pushButton->move(newX, newY);
    }
    else {
        QWidget::enterEvent(event);
    }
}
