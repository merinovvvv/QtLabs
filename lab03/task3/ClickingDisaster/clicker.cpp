#include "clicker.h"
#include "ui_clicker.h"

Clicker::Clicker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Clicker)
    , pressCount(0)
{
    ui->setupUi(this);
    wordCollection.push_back("click!");
    wordCollection.push_back("ouch!!");
}

Clicker::~Clicker()
{
    delete ui;
}

void Clicker::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        //QLabel *label = new QLabel("click", this);
        QLabel *label = new QLabel(wordCollection[pressCount], this);

        label->move(event->pos());
        label->show();
        label->setFixedSize(50, 25);
        labels.push_back(label);
    }
    QWidget::mousePressEvent(event);
}

void Clicker::keyPressEvent (QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        pressCount++;
        pressCount %= 2;
        for (size_t i = 0; i < labels.size(); ++i) {
            labels[i]->setText(wordCollection[pressCount]);
        }
    }

    QWidget::keyPressEvent(event);
}
