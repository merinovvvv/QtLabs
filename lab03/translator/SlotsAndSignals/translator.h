#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Translator;
}
QT_END_NAMESPACE

class Translator : public QWidget
{
    Q_OBJECT

public:
    Translator(QWidget *parent = nullptr);
    ~Translator();

private slots:
    void convert ();


private:
    QString comboBoxResult1;
    QString comboBoxResult2;

    Ui::Translator *ui;
};
#endif // TRANSLATOR_H
