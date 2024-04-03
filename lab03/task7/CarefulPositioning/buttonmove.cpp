#include "buttonmove.h"
#include "ui_buttonmove.h"
#include <QRect>
#include <QPushButton>
#include <QWidget>

ButtonMove::ButtonMove(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ButtonMove)
{
    ui->setupUi(this);
    ui->pushButton->resize(100, 30);
    //ui->pushButton->setGeometry(ui->horizontalSlider->pos().x(), ui->verticalSlider->pos().y(), 100, 30);
}

ButtonMove::~ButtonMove()
{
    delete ui;
}

void ButtonMove::on_verticalSlider_sliderMoved(int position)
{
    int buttonHeight = ui->pushButton->height();
    int sliderHeight = ui->verticalSlider->height();

    int newPosition = (sliderHeight - (sliderHeight - buttonHeight) * position / ui->verticalSlider->maximum()) - 20;

    ui->pushButton->move(ui->pushButton->x(), newPosition);
}


void ButtonMove::on_horizontalSlider_sliderMoved(int position)
{
    int buttonWidth = ui->pushButton->width();
    int sliderWidth = ui->horizontalSlider->width();

    int newPosition = ((sliderWidth - buttonWidth) * position / ui->horizontalSlider->maximum()) + 165;

    ui->pushButton->move(newPosition, ui->pushButton->y());
}

