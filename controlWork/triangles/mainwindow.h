#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QColor penColor;
    QColor brushColor;

    QListWidget *listWidget;

    QGraphicsScene* canvas;
    QGraphicsView* canvasView;

    QAction *chooseBrushColorAction;
    QAction *choosePenColorAction;

    QComboBox* comboSize;

    QPushButton* drawButton;
    QPushButton* saveButton;
    QPushButton* clearButton;

    QLineEdit* x1Line;
    QLineEdit* x2Line;
    QLineEdit* x3Line;

    QLineEdit* y1Line;
    QLineEdit* y2Line;
    QLineEdit* y3Line;

    QLineEdit* typeLine;

    void checkTriangleType();

    qreal x1, x2, x3, y1, y2, y3;

private slots:
    void showInfo();
    void chooseColor();
    void saveInfo();
    void drawTriangle();
    void clearTriangles();
};
#endif // MAINWINDOW_H
