#ifndef INTERMEDIATEFUNCTIONS_H
#define INTERMEDIATEFUNCTIONS_H

#include <QString>
#include <QTextStream>
#include <QSet>

class IntermediateFunctions
{
public:
    ~IntermediateFunctions() = default;
protected:
    static QSet <QChar> QSetMaker (const QString& word);
    static QString qstrRead ();
    static void sort(QString& str);
    static QMap <QChar, size_t> countLetters (const QString& str);
};

#endif // INTERMEDIATEFUNCTIONS_H
