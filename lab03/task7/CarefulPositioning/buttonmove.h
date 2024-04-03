#ifndef BUTTONMOVE_H
#define BUTTONMOVE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ButtonMove;
}
QT_END_NAMESPACE

class ButtonMove : public QWidget
{
    Q_OBJECT

public:
    ButtonMove(QWidget *parent = nullptr);
    ~ButtonMove();

private slots:
    void on_verticalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::ButtonMove *ui;

};
#endif // BUTTONMOVE_H
