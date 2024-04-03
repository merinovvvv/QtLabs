#ifndef PATTERNS_H
#define PATTERNS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Patterns;
}
QT_END_NAMESPACE

class Patterns : public QWidget
{
    Q_OBJECT

public:
    Patterns(QWidget *parent = nullptr);
    ~Patterns();

protected:
    void paintEvent (QPaintEvent *pe) override;

private:
    QVector <qint64> numbers = {1, 2, 3, 8, 5};
    void masItemsGen(QVector <qint64> & numbers);
    void doPainting();
    QVector <Qt::BrushStyle> patterns = {Qt::HorPattern, Qt::VerPattern, Qt::CrossPattern, Qt::Dense7Pattern, Qt::Dense6Pattern, Qt::Dense5Pattern, Qt::BDiagPattern, Qt::FDiagPattern, Qt::DiagCrossPattern};
    Ui::Patterns *ui;
};
#endif // PATTERNS_H
