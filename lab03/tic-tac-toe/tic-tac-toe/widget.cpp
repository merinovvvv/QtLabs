#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QComboBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1000, 600);

    // QMessageBox msgBox;

    // QPushButton *xButton = msgBox.addButton(tr("X"), QMessageBox::ActionRole);
    // QPushButton *oButton = msgBox.addButton(tr("0"), QMessageBox::ActionRole);

    // msgBox.setWindowTitle("X or 0?");
    // msgBox.setText("What does the first player choose?");
    // msgBox.setIcon(QMessageBox::Question);
    // msgBox.setWindowIcon(QIcon(":/images/img/think.png"));
    // msgBox.exec();

    // if (msgBox.clickedButton() == xButton) {
    //     imagesIndex = 0;

    // } else {
    //     imagesIndex = 1;
    // }



    //QMessageBox::StandardButton reply = QMessageBox::question(this, "X or 0?", "What does the first player choose?", xButton | oButton);


    //setStyleSheet("background-image: url(:/images/img/paper.jpeg);");

    gridlayout = new QGridLayout;
    buttons.resize(dim);
    for (size_t i = 0; i < dim; ++i) {
        buttons[i].resize(dim);
    }

    // QLabel* backgroundLabel = new QLabel;
    // QPixmap backgroundPixmap(":/images/img/paper.jpeg");

    // backgroundLabel->setPixmap(backgroundPixmap);
    // backgroundLabel->setScaledContents(true);

    // layout->addWidget(backgroundLabel, 0, 0, dim, dim);

    QPushButton* button;

    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            button = new QPushButton;
            button->setStyleSheet("background-color: transparent;");

            // QDesktopWidget *desktop = QApplication::desktop();
            // int screenWidth = desktop->width();
            // int screenHeight = desktop->height();

            int width = 240;
            int height = 200;

            button->setFixedSize(width, height);

            //button->setStyleSheet("border: 1px solid black;");

            //button->setStyleSheet("QPushButton { border: none; background-color: transparent; color: transparent; }");

            gridlayout->addWidget(button, i, j);
            buttons[i][j] = button;
            buttons[i][j]->setEnabled(false);

            QObject::connect(button, &QPushButton::clicked, this, &Widget::isClicked);
        }
    }

    //setLayout(layout);

    QLabel *crossWins = new QLabel;
    crossWins->setText("Elon Musk's wins:");
    xWins = new QLabel;
    xWins->setFixedSize(50, 50);
    xWins->setText(QString::number(xWinAmount));
    QVBoxLayout *vLayout1 = new QVBoxLayout; //layout for matching the wins of Elon with the text Elon's wins:

    vLayout1->addWidget(crossWins);
    vLayout1->addWidget(xWins);

    QLabel *zerosWins = new QLabel;
    zerosWins->setText("Opera's wins:");
    oWins = new QLabel;
    oWins->setFixedSize(50, 50);
    oWins->setText(QString::number(oWinAmount));
    QVBoxLayout *vLayout2 = new QVBoxLayout; //layout for matching the wins of Opera with the text Opera's wins:

    vLayout2->addWidget(zerosWins);
    vLayout2->addWidget(oWins);

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addLayout(vLayout1);
    hLayout1->addLayout(vLayout2);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QLabel *who = new QLabel;
    who->setText("Who is the 1st player?: ");
    combo = new QComboBox;
    combo->addItem("");
    combo->addItem("Elon Musk");
    combo->addItem("Opera");
    hLayout2->addWidget(who);
    hLayout2->addWidget(combo);

    QVBoxLayout *vLayout3 = new QVBoxLayout;
    vLayout3->addStretch();
    vLayout3->addLayout(hLayout2);
    vLayout3->addLayout(hLayout1);
    vLayout3->addStretch();


    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addLayout(vLayout3);
    hLayout3->addLayout(gridlayout);


    setLayout(hLayout3);

    images.push_back(QPixmap(":/images/img/cross.png"));
    images.push_back(QPixmap(":/images/img/zero.png"));


    QObject::connect(combo, &QComboBox::currentTextChanged, this, &Widget::comboIsChanged);

}

void Widget::paintEvent(QPaintEvent *event) {
    // Вызываем базовую реализацию paintEvent
    QWidget::paintEvent(event);

    // Создаем QPainter для рисования на виджете
    QPainter painter(this);

    // Устанавливаем цвет линии и толщину
    painter.setPen(QPen(Qt::black, 2));

    // Получаем количество строк и столбцов в gridlayout
    int rows = gridlayout->rowCount();
    int cols = gridlayout->columnCount();

    // Проходим по строкам и рисуем горизонтальные линии
    for (int i = 1; i < rows; ++i) {
        int y = gridlayout->cellRect(i, 0).top();
        painter.drawLine(buttons[0][0]->width() + 90, y, width() - 30, y);
    }

    // Проходим по столбцам и рисуем вертикальные линии
    for (int j = 1; j < cols; ++j) {
        int x = gridlayout->cellRect(0, j).left();
        painter.drawLine(x, 30, x, height() - 30);
    }
}


void Widget::isClicked () {

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton)
        return;

    else {
        clickedButton->setIcon(images[imagesIndex]);

        QSize iconSize(100, 100);

        clickedButton->setIconSize(iconSize);
        ++imagesIndex;
        imagesIndex %= images.size();
        clickedButton->setEnabled(false);

        //ERROR!!!

        if (combo->currentText() == "Elon Musk") {
            clickedButton->setObjectName(buttonNames[buttonIndex]);
            ++buttonIndex;
            buttonIndex %= buttonNames.size();
        }
        else {
            ++buttonIndex;
            if (buttonIndex == 2) {
                buttonIndex = 0;
            }
            clickedButton->setObjectName(buttonNames[buttonIndex]);
            buttonIndex %= buttonNames.size();
        }


        isWin();
    }

}

void Widget::comboIsChanged() {

    if (combo->currentText() != "") {

    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            buttons[i][j]->setEnabled(true);
        }
    }

    if (combo->currentText() == "Elon Musk") {
        imagesIndex = 0;
    }
    else {
        imagesIndex = 1;
    }
    combo->setEnabled(false);
    }
    else {
        for (size_t i = 0; i < dim; ++i) {
            for (size_t j = 0; j < dim; ++j) {
                buttons[i][j]->setEnabled(false);
            }
        }
    }
}

void Widget::isWin() {

    for (size_t i = 0; i < dim; ++i) { //rows cycle

        if (!buttons[i][0]->icon().isNull() && buttons[i][0]->icon().pixmap(buttons[i][0]->iconSize()).cacheKey() == buttons[i][1]->icon().pixmap(buttons[i][1]->iconSize()).cacheKey() && buttons[i][0]->icon().pixmap(buttons[i][0]->iconSize()).cacheKey() == buttons[i][2]->icon().pixmap(buttons[i][2]->iconSize()).cacheKey()) {
            if (buttons[i][0]->objectName() == "Elon Musk") {
                xWinAmount++;
                xWins->setText(QString::number(xWinAmount));
            }
            else {
                oWinAmount++;
                oWins->setText(QString::number(oWinAmount));
            }
            QMessageBox::StandardButton reply = QMessageBox::question(this, buttons[i][0]->objectName() + " wins!", "Do you want to play again?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // QCoreApplication::exit(0);
                // QProcess::startDetached(qApp->arguments()[0]);
                ButtonsDelete();
            }
            else {
                QCoreApplication::exit(0);
            }
        }
    }

    for (size_t i = 0; i < dim; ++i) { //columns cycle
        if (!buttons[0][i]->icon().isNull() && buttons[0][i]->icon().pixmap(buttons[0][i]->iconSize()).cacheKey() == buttons[1][i]->icon().pixmap(buttons[1][i]->iconSize()).cacheKey() && buttons[0][i]->icon().pixmap(buttons[0][i]->iconSize()).cacheKey() == buttons[2][i]->icon().pixmap(buttons[2][i]->iconSize()).cacheKey()) {

            if (buttons[0][i]->objectName() == "Elon Musk") {
                xWinAmount++;
                xWins->setText(QString::number(xWinAmount));
            }
            else {
                oWinAmount++;
                oWins->setText(QString::number(oWinAmount));
            }

            QMessageBox::StandardButton reply = QMessageBox::information(this, buttons[0][i]->objectName() + " wins!", "Do you want to play again?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // QCoreApplication::exit(0);
                // QProcess::startDetached(qApp->arguments()[0]);
                ButtonsDelete();
            }
            else {
                QCoreApplication::exit(0);
            }
        }
    }

    if (!buttons[0][0]->icon().isNull() && buttons[0][0]->icon().pixmap(buttons[0][0]->iconSize()).cacheKey() == buttons[1][1]->icon().pixmap(buttons[1][1]->iconSize()).cacheKey() && buttons[0][0]->icon().pixmap(buttons[0][0]->iconSize()).cacheKey() == buttons[2][2]->icon().pixmap(buttons[2][2]->iconSize()).cacheKey()) {

        if (buttons[0][0]->objectName() == "Elon Musk") {
            xWinAmount++;
            xWins->setText(QString::number(xWinAmount));
        }
        else {
            oWinAmount++;
            oWins->setText(QString::number(oWinAmount));
        }

        QMessageBox::StandardButtons reply = QMessageBox::information(this, buttons[0][0]->objectName() + " wins!", "Do you want to play again?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // QCoreApplication::exit(0);
            // QProcess::startDetached(qApp->arguments()[0]);
            ButtonsDelete();
        }
        else {
            QCoreApplication::exit(0);
        }
    }

    if (!buttons[2][0]->icon().isNull() && buttons[2][0]->icon().pixmap(buttons[2][0]->iconSize()).cacheKey() == buttons[1][1]->icon().pixmap(buttons[1][1]->iconSize()).cacheKey() && buttons[2][0]->icon().pixmap(buttons[2][0]->iconSize()).cacheKey() == buttons[0][2]->icon().pixmap(buttons[0][2]->iconSize()).cacheKey()) {

        if (buttons[2][0]->objectName() == "Elon Musk") {
            xWinAmount++;
            xWins->setText(QString::number(xWinAmount));
        }
        else {
            oWinAmount++;
            oWins->setText(QString::number(oWinAmount));
        }

        QMessageBox::StandardButtons reply = QMessageBox::information(this, buttons[2][0]->objectName() + " wins!", "Do you want to play again?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // QCoreApplication::exit(0);
            // QProcess::startDetached(qApp->arguments()[0]);
            ButtonsDelete();
        }
        else {
            QCoreApplication::exit(0);
        }
    }

    if (!buttons[0][0]->icon().isNull() && !buttons[0][1]->icon().isNull() && !buttons[0][2]->icon().isNull() && !buttons[1][0]->icon().isNull() && !buttons[1][1]->icon().isNull() && !buttons[1][2]->icon().isNull() && !buttons[2][0]->icon().isNull() && !buttons[2][1]->icon().isNull() && !buttons[2][2]->icon().isNull()) {
        QMessageBox::StandardButtons reply = QMessageBox::information(this, "A tie!", "Do you want to play again?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // QCoreApplication::exit(0);
            // QProcess::startDetached(qApp->arguments()[0]);
            ButtonsDelete();
        }
        else {
            QCoreApplication::exit(0);
        }
    }

}

void Widget::ButtonsDelete () {
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            buttons[i][j]->setIcon(QIcon());
            //buttons[i][j]->setEnabled(true);

        }
    }
    combo->setCurrentText("");
    combo->setEnabled(true);
    imagesIndex = 0;
    buttonIndex = 0;
}

Widget::~Widget()
{
    delete ui;
}
