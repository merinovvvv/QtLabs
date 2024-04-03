#include "buttonsandboxes.h"
#include "ui_buttonsandboxes.h"

ButtonsAndBoxes::ButtonsAndBoxes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ButtonsAndBoxes)
{
    ui->setupUi(this);
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(CheckBoxIsOn(int)));
    connect(ui->checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(CheckBox2IsOn(int)));
    connect(ui->checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(CheckBox4IsOn(int)));
    connect(ui->checkBox_5, SIGNAL(stateChanged(int)), this, SLOT(CheckBox5IsOn(int)));
    connect(ui->checkBox_6, SIGNAL(stateChanged(int)), this, SLOT(CheckBox6IsOn(int)));
}

ButtonsAndBoxes::~ButtonsAndBoxes()
{
    delete ui;
}

void ButtonsAndBoxes::CheckBoxIsOn(int state) {
    if (state == Qt::Checked) {
        ui->pushButton->hide();
    }
    else {
        ui->pushButton->show();
    }
}

void ButtonsAndBoxes::CheckBox2IsOn(int state) {
    if (state == Qt::Checked) {
        ui->pushButton_2->hide();
    }
    else {
        ui->pushButton_2->show();
    }
}

void ButtonsAndBoxes::CheckBox4IsOn(int state) {
    if (state == Qt::Checked) {
        ui->pushButton_3->hide();
    }
    else {
        ui->pushButton_3->show();
    }
}

void ButtonsAndBoxes::CheckBox5IsOn(int state) {
    if (state == Qt::Checked) {
        ui->pushButton_5->hide();
    }
    else {
        ui->pushButton_5->show();
    }
}

void ButtonsAndBoxes::CheckBox6IsOn(int state) {
    if (state == Qt::Checked) {
        ui->pushButton_6->hide();
    }
    else {
        ui->pushButton_6->show();
    }
}
