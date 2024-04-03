#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

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

protected:
    void paintEvent(QPaintEvent *e) override;
    void drawHistogram(QPainter *qp);

private:
    Ui::Widget *ui;
    QVector <qint64> valueList;
    //QPainter qp;
};
#endif // WIDGET_H
