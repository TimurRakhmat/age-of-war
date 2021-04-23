#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bkgnd = new QPixmap(":/image/Menu.jpg");
    about = new QPixmap(":/image/about.jpg");

    this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowState(Qt::WindowMaximized);
    music = new QSound(":/sound/menuSound.wav");
    music->setLoops(QSound::Infinite);
    music->play();
    drawMenu();
    this->setWindowTitle("Age of War");

    this->show();
}

MainWindow::~MainWindow()
{
    music->stop();
    delete music;
    delete ui;
    delete btnAbout;
    delete btnExit;
    delete btnStart;
    delete layout;
    delete bkgnd;
}

void MainWindow::drawMenu()
{
    QPixmap bk = bkgnd->scaled(this->size(), Qt::IgnoreAspectRatio);
    //bkgnd = bkgnd.scaled((800, 600), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bk);
    this->setPalette(palette);

    layout = new QVBoxLayout(this->centralWidget());
    //this->setLayout(layout);

    btnStart = new QPushButton("Start");
    btnAbout = new QPushButton("About");
    btnExit = new QPushButton("Exit");

    layout->addWidget(btnStart);
    layout->addWidget(btnAbout);
    layout->addWidget(btnExit);

    layout->setAlignment(Qt::AlignHCenter);

    connect(btnStart, &QPushButton::pressed, this, &MainWindow::goToGame);
    connect(btnAbout, &QPushButton::pressed, this, &MainWindow::goToAbout);
    connect(btnExit, &QPushButton::pressed, qApp, &QApplication::quit);
}

void MainWindow::drawAbout()
{
    QPixmap bk = about->scaled(this->size(), Qt::IgnoreAspectRatio);
    //bkgnd = bkgnd.scaled((800, 600), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bk);
    this->setPalette(palette);

    layout = new QVBoxLayout(this->centralWidget());
    //this->setLayout(layout);

    btnExit = new QPushButton("return");

    layout->addWidget(btnExit);

    layout->setAlignment(Qt::AlignBottom);

    connect(btnExit, &QPushButton::pressed, this, &MainWindow::goToMenu);
}

void MainWindow::startGame()
{
    try {
    view = new GraphicsView(this);
    connect(view, &GraphicsView::exitSignal, this, &MainWindow::goToMenuFromGame);
    }
    catch (...)
    {
        qDebug() << "gameError";
    }
}

void MainWindow::goToAbout()
{
    delete btnAbout;
    delete btnExit;
    delete btnStart;
    delete layout;

    drawAbout();
}

void MainWindow::goToMenu()
{
    delete btnExit;
    delete layout;

    drawMenu();
}

void MainWindow::goToMenuFromGame()
{
    try {
    delete view;
    drawMenu();
    }
    catch (...)
    {
        qDebug() << "returnGameError";
    }
}

void MainWindow::goToGame()
{
    delete btnAbout;
    delete btnExit;
    delete btnStart;
    delete layout;

    startGame();
}
