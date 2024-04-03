#ifndef FUNNYBUTTON_H
#define FUNNYBUTTON_H

#include <QWidget>
#include <QRandomGenerator>
#include <QColor>
#include <QPushButton>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class FunnyButton;
}
QT_END_NAMESPACE

class FunnyButton : public QWidget
{
    Q_OBJECT

public:
    FunnyButton(QWidget *parent = nullptr);
    ~FunnyButton();

private slots:
    void on_pushButton_clicked();
    void mouseMoveEvent (QMouseEvent *event);

private:
    Ui::FunnyButton *ui;
    QColor GenerateRandomColor();
};
#endif // FUNNYBUTTON_H
