#ifndef CLICKER_H
#define CLICKER_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Clicker;
}
QT_END_NAMESPACE

class Clicker : public QWidget
{
    Q_OBJECT

public:
    Clicker(QWidget *parent = nullptr);
    ~Clicker();

protected:
    void mousePressEvent (QMouseEvent* event) override;
    void keyPressEvent (QKeyEvent* event) override;

private:
    Ui::Clicker *ui;
    QVector <QLabel*> labels;
    QVector <QString> wordCollection;
    int pressCount = 0;
};
#endif // CLICKER_H
