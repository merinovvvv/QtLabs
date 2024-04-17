#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRandomGenerator>

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
    void dotsColorInit();


private:
    Ui::Widget *ui;
    int dots_;
    QVector <QVector <QColor>> plazma_;
    void fillPlazma (int& , int&, int&, int&);

    const int delta = 30;

protected:
    void paintEvent (QPaintEvent *qp) override;
};
#endif // WIDGET_H
