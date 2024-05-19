#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class Application;
}
QT_END_NAMESPACE

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private:
    Ui::Application *ui;

    QPushButton* square;
    QPushButton* ellipse;
    QPushButton* text;
    QGraphicsScene *scene;
    QGraphicsView *view;

    QString currentName;

    void mousePressEvent (QMouseEvent* event) override;
    void paintEvent (QPaintEvent* event) override;
    void draw(QPainter* qp);
    void drawSquare(QPainter* qp);
    void drawEllipse(QPainter* qp);
    void drawText(QPainter* qp);

private slots:
    void quitApp();
    void textChosen();
    void squareChosen();
    void ellipseChosen();

protected:
    //bool event(QEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;
    // void paintEvent(QPaintEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif // APPLICATION_H
