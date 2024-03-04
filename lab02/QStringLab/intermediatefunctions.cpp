#include "intermediatefunctions.h"


QSet <QChar> IntermediateFunctions::QSetMaker (const QString& word) {
    QSet <QChar> setword;

    foreach (QChar ch, word) {
        setword.insert(ch);
    }

    return setword;
}

QString IntermediateFunctions::qstrRead () {

    QTextStream in(stdin);

    QString word;

    in >> word;

    return word;
}

void IntermediateFunctions::sort(QString& str) {
    QList<QChar> list;

    for (size_t i = 0; i < str.size(); ++i) {
        list.append(str.at(i));
    }


    std::sort(list.begin(), list.end());

    str.clear();

    for (const QChar &ch : list) {
        str.append(ch);
    }
}

QMap <QChar, size_t> IntermediateFunctions::countLetters (const QString& str) {
    QMap<QChar, size_t> counts;
    for (QChar letter : str) {
        counts[letter]++;
    }
    return counts;
}
