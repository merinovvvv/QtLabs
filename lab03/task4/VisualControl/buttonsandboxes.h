#ifndef BUTTONSANDBOXES_H
#define BUTTONSANDBOXES_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ButtonsAndBoxes;
}
QT_END_NAMESPACE

class ButtonsAndBoxes : public QWidget
{
    Q_OBJECT

public:
    ButtonsAndBoxes(QWidget *parent = nullptr);
    ~ButtonsAndBoxes();

private slots:
    void CheckBoxIsOn(int state);
    void CheckBox2IsOn(int state);
    void CheckBox4IsOn(int state);
    void CheckBox5IsOn(int state);
    void CheckBox6IsOn(int state);

private:
    Ui::ButtonsAndBoxes *ui;
};
#endif // BUTTONSANDBOXES_H
