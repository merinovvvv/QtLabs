#ifndef SPAWN_H
#define SPAWN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class Spawn;
}
QT_END_NAMESPACE

class Spawn : public QWidget
{
    Q_OBJECT

public:
    Spawn(QWidget *parent = nullptr);
    ~Spawn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Spawn *ui;
    QString comboBoxResult;
    size_t spinBoxResult;
};
#endif // SPAWN_H
