#include "clicker.h"
#include "ui_clicker.h"

Clicker::Clicker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Clicker)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->pushButton->setEnabled(false);
}

Clicker::~Clicker()
{
    delete ui;
}

void Clicker::on_pushButton_clicked()
{
    if (ui->spinBox->value() != spinBoxResult) {
        ui->progressBar->setValue(0);
        ui->spinBox->setEnabled(false);
        spinBoxResult = ui->spinBox->value();
        ui->progressBar->setMaximum(spinBoxResult);
    }

    size_t newValue = ui->progressBar->value() + 1;
    ui->progressBar->setValue(newValue);
}


void Clicker::on_spinBox_valueChanged(int arg1)
{
    if (ui->spinBox->value() == 0) {
        ui->pushButton->setEnabled(false);
    }
    else {
        ui->pushButton->setEnabled(true);
    }
}

