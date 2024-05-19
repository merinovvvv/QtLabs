#include "application.h"
#include "ui_application.h"

#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

Application::Application(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);

    QMenuBar *menuBar = new QMenuBar(this);


    QAction *quit = new QAction("&Quit", menuBar);
    QAction *clock = new QAction("&Clock",menuBar);

    menuBar->addAction(quit);
    menuBar->addAction(clock);

    square = new QPushButton;
    ellipse = new QPushButton;
    text = new QPushButton();

    square->setIcon(QIcon(":/resource/img/square.png"));
    ellipse->setIcon(QIcon(":/resource/img/ellipse.png"));
    text->setIcon(QIcon(":/resource/img/text.png"));

    QHBoxLayout *chooseFigureLayout = new QHBoxLayout();
    chooseFigureLayout->addWidget(text);
    chooseFigureLayout->addWidget(square);
    chooseFigureLayout->addWidget(ellipse);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addLayout(chooseFigureLayout);

    scene = new QGraphicsScene();
    view = new QGraphicsView();

    view->setScene(scene);


    mainLayout->addWidget(view);
    setLayout(mainLayout);


    connect(quit, SIGNAL(triggered()), this, SLOT(quitApp()));
    connect (square, SIGNAL(clicked()), this, SLOT(squareChosen()));
    connect (ellipse, SIGNAL(clicked()), this, SLOT(ellipseChosen()));
    connect (square, SIGNAL(clicked()), this, SLOT(textChosen()));
}

void Application::quitApp() {
    qApp->quit();
}

void Application::squareChosen() {
    currentName = "square";
}

void Application::ellipseChosen() {
    currentName = "ellipse";
}

void Application::textChosen() {
    currentName = "text";
}

void Application::mousePressEvent (QMouseEvent* event) {

}

void Application::paintEvent (QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter qp(this);
    draw(&qp);
}

void Application::draw(QPainter* qp) {
    if (currentName == "square") {
        drawSquare(qp);
    } else if (currentName == "ellipse") {
        drawEllipse(qp);
    } else if (currentName == "text") {
        drawText(qp);
    } else {
        qDebug() << "Error: drawing incorrect item";
    }
}

Application::~Application()
{
    delete ui;
}
