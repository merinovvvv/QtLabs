#include <QSet>
#include <QStack>

#include "task.h"
#include "intermediatefunctions.h"

void Task::canBuildWordNoRepeat () {

    QString word1;
    QString word2;

    QTextStream out(stdout);

    out << "word build program without repeats.\n";

    out << "Input the first word:\n";

    out.flush();

    word1 = IntermediateFunctions::qstrRead();

    out << "Input the second word:\n";

    out.flush();

    word2 = IntermediateFunctions::qstrRead();

    QSet <QChar> set1 = IntermediateFunctions::QSetMaker (word1);

    for (size_t i = 0; i < word1.size(); ++i) {
        if (set1.find(word2.at(i)) == set1.end()) {
            out << "It is not possible to build the second word with the letters of the first one.\n\n\n";
            return;

        }
    }
    out << "It is possible to build the second word with the letters of the first one.\n\n\n";
}

void Task::canBuildWordWithRepeats () {
    QString word1;
    QString word2;

    QTextStream out(stdout);

    out << "word build program with repeats.\n";

    out << "Input the first word:\n";

    out.flush();

    word1 = IntermediateFunctions::qstrRead();

    out << "Input the second word:\n";

    out.flush();

    word2 = IntermediateFunctions::qstrRead();

    QMap<QChar, size_t> word1Counts = IntermediateFunctions::countLetters(word1);
    QMap<QChar, size_t> word2Counts = IntermediateFunctions::countLetters(word2);

    QMapIterator<QChar, size_t> i(word2Counts);
        while (i.hasNext()) {
            i.next();
            QChar letter = i.key();
            size_t count = i.value();
            if (word1Counts[letter] < count) {
                out << "It is not possible to build the second word with the letters of the first one.\n\n\n";
            }
        }
        out << "It is possible to build the second word with the letters of the first one.\n\n\n";
    }

    /*for (const auto& pair : word2Counts) {
        QChar letter = pair.first;
        size_t count = pair.second;
        if (word1Counts[letter] < count) {
             out << "It is not possible to build the second word with the letters of the first one.\n\n\n";
        }
    }
     out << "It is possible to build the second word with the letters of the first one.\n\n\n";
}*/

void Task::TheLongestWord () {

    QTextStream out(stdout);

     out << "the longest word program.\n";

    QTextStream in(stdin);

    QString sentence;

    out << "Input the sentence:\n";

    out.flush();

    sentence = in.readLine();

    QVector <QString> words;

    QStringList wordList = sentence.split(" ");

    foreach (QString qstr, wordList) {
        words.push_back(qstr);
    }

    QString max = words[0];

    for (size_t i = 0; i < words.size(); ++i) {
        if (words.at(i).size() > max.size()) {
            max = words.at(i);
        }
    }

    out << "The result is: " << max << "\n\n\n";
}

void Task::BracketsCorrect () {
    QTextStream out(stdout);

    out << "the brackets correct program.\n";

    QTextStream in(stdin);

    QString text;

    out << "Input the text:\n";

    out.flush();

    text = in.readLine();

    QStack <QChar> bracketsStack;

    size_t incOpenBrackets = 0;
    size_t incCloseBracketsIndex = 0;

    for (int i = 0; i < text.size(); ++i) {
        if (text.at(i).isPunct()) {
        if (text.at(i) == '(') {
            bracketsStack.push(text.at(i));
        }
        else if (text.at(i) == ')') {
            if (bracketsStack.isEmpty()) {
                incCloseBracketsIndex = i;
                break;
            }
            else if (bracketsStack.top() == '(') {
                bracketsStack.pop();
                }
            }
        }
    }

    incOpenBrackets = bracketsStack.size();

    if (bracketsStack.isEmpty() && incCloseBracketsIndex == 0) {
        out << "YES.\n";
    }

    else {
        if (!bracketsStack.isEmpty() && incCloseBracketsIndex == 0) {
        out << "NO.\n";
        out << "There is (are) " << incOpenBrackets << " incorrect open bracket(s).\n";
        }
        else if (bracketsStack.isEmpty() && incCloseBracketsIndex != 0) {
            out << "NO.\n";
            out << "The first index of incorrect close bracket is " << incCloseBracketsIndex << '\n';
        }
    }
}
