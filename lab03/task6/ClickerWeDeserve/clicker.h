#ifndef CLICKER_H
#define CLICKER_H

#include <QWidget>

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

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::Clicker *ui;
    size_t spinBoxResult;
};
#endif // CLICKER_H
