#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>

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

    struct GraphParams {
        QString type;
        QColor color;
        double k;
        double a, b, c, d;
        double xMin, xMax, yMin, yMax;
        double xMinWidget;
        double xMaxWidget;
        double yMinWidget;
        double yMaxWidget;
        QList <QPointF> pointList;
    };

    QList<GraphParams> graphs;

    QList <QGraphicsLineItem*> lines;

    QComboBox* graphChoose;
    QComboBox* colorChoose;

    qreal x_min_;
    qreal x_min_widget;

    qreal x_max_;
    qreal x_max_widget;

    qreal y_min_;
    qreal y_min_widget;

    qreal y_max_;
    qreal y_max_widget;

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
    QLineEdit* xValueLine;
    QLineEdit* yValueLine;

    QPushButton* drawButton;
    QPushButton* clearButton;
    QPushButton* calcButton;

    QGraphicsScene* graphSurface;
    QGraphicsView* graphShow;

    QString linear = "y(x) = kx+b";
    QString quadro = "y(x) = ax^2+bx+c";
    QString cubic = "y(x) = ax^3+bx^2+cx+d";
    QString random = "у(x) = ax^b+sin(cx)";

    QColor color;

    qreal step = 50;

    qreal x_value;
    qreal y_value;

    // qreal leftBound;
    // qreal bottomBound;

    QList <QString> graphList;

    void drawCoordinatePlane(QGraphicsScene*);
    void redrawGraphs();
    void drawSingleGraph(GraphParams& params);

protected:
    void mousePressEvent(QMouseEvent* event) override;


private slots:
    void graphChanged();
    void colorChanged();
    void drawGraph();
    void clearGraph();
    void calcValue();
    void zoomIn();
    void zoomOut();
};
#endif // WIDGET_H
