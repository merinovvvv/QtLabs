#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QSlider>
#include <QBasicTimer>

enum class HorizontalDirectionTypes {
    kLeft,
    kRight,
};

// enum class VerticalDirectionTypes {
//     kTop,
//     kBottom,
// };

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void setScene();
    void setHero();

    void timerEvent(QTimerEvent* event) override;

private:
    Ui::Widget *ui;

    QGraphicsScene* scene_;
    QPixmap krusty_;
    QPixmap spongebob_;
    QGraphicsView* view_;

    QSlider* length_;
    QSlider* height_;
    QGraphicsPixmapItem* spongebob_item_;

    int spongebob_width_;
    int spongebob_height_;

    double x_{0}, y_{0};
    HorizontalDirectionTypes directionH_{HorizontalDirectionTypes::kRight};
    //VerticalDirectionTypes directionV_{VerticalDirectionTypes::kTop};
    double jump_length_{60};
    double jump_height_{100};

    QBasicTimer animation_timer_;

    int widthWidget_ = 1000;
    int heightWidget_ = 550;
};
#endif // WIDGET_H
