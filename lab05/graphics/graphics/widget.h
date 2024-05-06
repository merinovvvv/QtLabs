#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

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

    Widget(const Widget& other) = delete;
    Widget& operator =(const Widget& other) = delete;
    Widget(Widget&& other) = delete;
    Widget& operator =(Widget&& other) = delete;

    //void paintEvent(QPaintEvent* event) override;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);
    void on_lineEdit_6_textChanged(const QString &arg1);
    void on_lineEdit_7_textChanged(const QString &arg1);
    void on_lineEdit_8_textChanged(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    QGraphicsScene* scene_;
    QPixmap field_;

    QPen pen_;

    qreal x_min = 20;
    qreal x_max = 40;
    qreal y_min = -20;
    qreal y_max = 40;
    qreal a_ = 0.1;
    qreal b_ = 0.5;
    qreal c_ = 0;
    qreal d_ = 0;

    void drawCoordNet();
    void drawGraph();
};
#endif // WIDGET_H
