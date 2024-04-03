#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>

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

private slots:
    void isClicked();
    void comboIsChanged();

private:
    QComboBox *combo;
    Ui::Widget *ui;
    QVector <QVector <QPushButton*>> buttons;
    QVector <QPixmap> images;
    QVector <QString> buttonNames = {"Elon Musk", "Opera"};
    size_t dim = 3;
    size_t imagesIndex;
    size_t buttonIndex = 0;
    void isWin();
    void ButtonsDelete ();
    QLabel *oWins;
    QLabel *xWins;
    size_t xWinAmount = 0;
    size_t oWinAmount = 0;
    QGridLayout *gridlayout = new QGridLayout;

protected:
    void paintEvent (QPaintEvent *event) override;
};
#endif // WIDGET_H
