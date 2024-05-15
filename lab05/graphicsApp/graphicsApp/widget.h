#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>

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

private:
    Ui::Widget *ui;

    QComboBox* graphChoose;
    QComboBox* colorChoose;

    qreal x_min_;
    qreal x_max_;
    qreal y_min_;
    qreal y_max_;

    qreal k_;
    qreal a_;
    qreal b_;
    qreal c_;
    qreal d_;

    QLineEdit* xMinLine;
    QLineEdit* xMaxLine;
    QLineEdit* yMinLine;
    QLineEdit* yMaxLine;

    QLineEdit* kLine;
    QLineEdit* aLine;
    QLineEdit* bLine;
    QLineEdit* cLine;
    QLineEdit* dLine;

    QPushButton* drawButton;
    QPushButton* clearButton;

    QGraphicsScene* graphSurface;
    QGraphicsView* graphShow;

    QString linear = "y(x) = kx+b";
    QString quadro = "y(x) = ax^2+bx+c";
    QString cubic = "y(x) = ax^3+bx^2+cx+d";
    QString random = "у(x) = ax^b+sin(cx)";

    QColor color;

    qreal step = 10;

    // qreal leftBound;
    // qreal bottomBound;

    void drawCoordinatePlane(QGraphicsScene*);

private slots:
    void graphChanged();
    void colorChanged();
    void drawGraph();
    void clearGraph();


};
#endif // WIDGET_H
