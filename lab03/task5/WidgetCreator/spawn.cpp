#include <QRandomGenerator>

#include "spawn.h"
#include "ui_spawn.h"

Spawn::Spawn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Spawn)
{
    ui->setupUi(this);
}

Spawn::~Spawn()
{
    delete ui;
}

void Spawn::on_pushButton_clicked()
{
    spinBoxResult = ui->spinBox->value();
    comboBoxResult = ui->comboBox->currentText();

    int widgetWidth = this->width();
    int widgetHeight = this->height();


    for (size_t i = 0; i < spinBoxResult; ++i) {

        int newX = QRandomGenerator::global()->bounded(widgetWidth - ui->pushButton->width());
        int newY = QRandomGenerator::global()->bounded(widgetHeight - ui->pushButton->height());

        if (comboBoxResult == "PushButton") {
            QPushButton *button = new QPushButton("pushButton", this);

            button->move(newX, newY);
            button->show();
        }
        else if (comboBoxResult == "LineEdit") {
            QLineEdit *line = new QLineEdit("lineEdit", this);

            line->move(newX, newY);
            line->show();
        }
        else if (comboBoxResult == "Label") {
            QLabel *label = new QLabel("label", this);

            label->move(newX, newY);
            label->show();
        }
    }
}
