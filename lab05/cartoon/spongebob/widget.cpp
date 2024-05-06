#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtMath>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
    scene_(new QGraphicsScene(this)),
    krusty_(":/images/img/rest.jpg"),
    spongebob_(":/images/img/bob.png"),
    view_(new QGraphicsView(this)),
    length_(new QSlider(Qt::Horizontal, this)),
    height_(new QSlider(Qt::Vertical, this))
{
    ui->setupUi(this);

    setWindowTitle("AM AM AM AM");
    setWindowIcon(QIcon(":/images/img/burg.png"));



    setFixedSize(widthWidget_, heightWidget_);
    length_->setGeometry(0, heightWidget_ - 50, widthWidget_ - 50, 50);
    length_->setMaximum(100);
    length_->setMinimum(1);
    length_->setValue(50);

    height_->setGeometry(widthWidget_ - 50, 0, 50, heightWidget_ - 50);
    height_->setMaximum(100);
    height_->setMinimum(1);
    height_->setValue(50);

    setScene();
    setHero();

    connect(length_, &QSlider::valueChanged, this, [&] {
        jump_length_ = length_->value() * 1.2;
    });

    connect(height_, &QSlider::valueChanged, this, [&] {
        jump_height_ = height_->value() * 2.0;
    });

    animation_timer_.start(2, this);

}

void Widget::setScene() {
    scene_->addPixmap(krusty_);
    view_->setScene(scene_);
    view_->setFixedSize(1024, 576);
}

void Widget::setHero() {
    spongebob_item_ = scene_ -> addPixmap(spongebob_);
    spongebob_item_->setPos(0, 100);
    spongebob_width_ = static_cast<int>(spongebob_item_->boundingRect().width());

}

void Widget::timerEvent(QTimerEvent* event) {
    if (event->timerId() == animation_timer_.timerId()) {
        y_ = -abs(jump_height_ * qSin(x_ / jump_length_));

        spongebob_item_->setPos(x_ , y_ + 100);
        if (directionH_ == HorizontalDirectionTypes::kRight && x_ + spongebob_width_ >= widthWidget_) {
            directionH_ = HorizontalDirectionTypes::kLeft;
            spongebob_item_->setPixmap(spongebob_.transformed(QTransform().scale(-1, 1)));
        } else if (directionH_ == HorizontalDirectionTypes::kLeft && x_ <= 0) {
            directionH_ = HorizontalDirectionTypes::kRight;
            spongebob_item_->setPixmap(spongebob_);
        }

        // if (directionV_ == VerticalDirectionTypes::kBottom && y_ + spongebob_height_ >= heightWidget_) {
        //     directionV_ = VerticalDirectionTypes::kTop;
        //     spongebob_item_->setPixmap(spongebob_.transformed(QTransform().scale(1, -1)));
        // } else if (directionV_ == VerticalDirectionTypes::kTop && y_ <= 0) {
        //     directionV_ = VerticalDirectionTypes::kBottom;
        //     spongebob_item_->setPixmap(spongebob_);
        // }

        if (directionH_ == HorizontalDirectionTypes::kRight) {
            x_ += 0.5;
        } else {
            x_ -= 0.5;
        }

        // if (directionV_ == VerticalDirectionTypes::kBottom) {
        //     y_ += 0.5;
        // } else {
        //     y_ -= 0.5;
        // }

        repaint();
    }
}



Widget::~Widget()
{
    delete ui;
}
