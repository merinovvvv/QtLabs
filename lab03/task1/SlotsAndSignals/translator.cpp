#include "translator.h"
#include "ui_translator.h"

Translator::Translator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Translator)
{
    ui->setupUi(this);
    connect (ui->pushButton, &QPushButton::clicked, this, &Translator::convert);
    this->resize(1920, 1080);

}

Translator::~Translator()
{
    delete ui;
}

void Translator::convert() {

    bool isOk;

    comboBoxResult1 = ui->comboBox->currentText();
    comboBoxResult2 = ui->comboBox_2->currentText();

    int baseInitial = comboBoxResult1.toInt();
    int baseResult = comboBoxResult2.toInt();

    QString input = ui->lineEdit->text();
    long num = input.toLong(&isOk, baseInitial);

    ui->lineEdit_2->setText(QString::number(num, baseResult));

}
