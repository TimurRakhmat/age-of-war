#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bkgnd = new QPixmap(":/image/moto_cenz.jpg");
    about = new QPixmap(":/image/about.jpg");
    def_img = new QPixmap(":/image/Eren.jpg");
    vic_img = new QPixmap(":/image/victory.jpg");



    this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowState(Qt::WindowMaximized);
    music = new QSound(":/sound/menuSound.wav");
    music->setLoops(QSound::Infinite);
    //music->play();
    drawMenu();
    this->setWindowTitle("Age of War");

    this->show();
}

MainWindow::~MainWindow()
{
    //music->stop();
    delete music;
    delete ui;
    delete btnAbout;
    delete btnExit;
    delete about;
    delete def_img;
    delete vic_img;
    delete btnStart;
    delete layout;
    delete bkgnd;
}

void MainWindow::drawMenu()
{
    QPixmap bk = bkgnd->scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bk);
    this->setPalette(palette);

    layout = new QVBoxLayout(this->centralWidget());

    btnStart = new QPushButton("Start");
    btnAbout = new QPushButton("About");
    btnExit = new QPushButton("Exit");

    setStyle(btnAbout);
    setStyle(btnExit);
    setStyle(btnStart);

    layout->addWidget(btnStart);
    layout->addWidget(btnAbout);
    layout->addWidget(btnExit);

    layout->setAlignment(Qt::AlignRight);

    connect(btnStart, &QPushButton::pressed, this, &MainWindow::goToGame);
    connect(btnAbout, &QPushButton::pressed, this, &MainWindow::goToAbout);
    connect(btnExit, &QPushButton::pressed, qApp, &QApplication::quit);
}

void MainWindow::drawAbout()
{
    QPixmap bk = about->scaled(this->size(), Qt::IgnoreAspectRatio);; //->scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bk);
    this->setPalette(palette);

    layout = new QVBoxLayout(this->centralWidget());
    QHBoxLayout hlay;

    btnExit = new QPushButton("return");
    btnExit->setGeometry(width()/ 2 - 60, height() - 100, 180, 60);
    setStyle(btnExit);

    layout->addLayout(&hlay);
    hlay.addWidget(btnExit);
    layout->setAlignment(Qt::AlignBottom);
    hlay.setAlignment(Qt::AlignCenter);

    connect(btnExit, &QPushButton::pressed, this, &MainWindow::goToMenu);
}

void MainWindow::startGame()
{
    view = new GraphicsView(this);
    connect(view, &GraphicsView::exitSignal, this, &MainWindow::goToMenuFromGame);
    connect(view, &GraphicsView::defeat, this, &MainWindow::defeat);
    connect(view, &GraphicsView::victory, this, &MainWindow::victory);
}

void MainWindow::setVictory()
{
    QPixmap bk = vic_img->scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bk);
    this->setPalette(palette);

    layout = new QVBoxLayout(this->centralWidget());
    QHBoxLayout hlay;

    btnExit = new QPushButton("return");
    btnExit->setGeometry(this->width()/ 2 - 60, this->height() - 100, 180, 60);
    setStyle(btnExit);

    layout->addLayout(&hlay);
    hlay.addWidget(btnExit);
    layout->setAlignment(Qt::AlignBottom);
    hlay.setAlignment(Qt::AlignCenter);

    connect(btnExit, &QPushButton::pressed, this, &MainWindow::goToMenu);
}

void MainWindow::setDefeat()
{
    QPixmap bk = def_img->scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bk);
    this->setPalette(palette);

    layout = new QVBoxLayout(this->centralWidget());
    QHBoxLayout hlay;

    btnExit = new QPushButton("return");
    btnExit->setGeometry(this->width()/ 2 - 60, this->height() - 100, 180, 60);
    setStyle(btnExit);

    layout->addLayout(&hlay);
    hlay.addWidget(btnExit);
    layout->setAlignment(Qt::AlignBottom);
    hlay.setAlignment(Qt::AlignCenter);

    connect(btnExit, &QPushButton::pressed, this, &MainWindow::goToMenu);
}

void MainWindow::setStyle(QPushButton *btn)
{
    btn->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                                    "font-size: 45px;"
                                    "color:rgba(255,255,255,255);"
                                    "border-radius: 8px;"
                                    "border-width: 3px;"
                                    "border-image: 9,2,5,2; "
                                    "background-position: top left;"
                                    "background-origin: content;"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                                    "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}"
                                    );
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
    delete view;
    drawMenu();
}

void MainWindow::victory()
{
    delete view;
    setVictory();
}

void MainWindow::defeat()
{
    delete view;
    setDefeat();
}

void MainWindow::goToGame()
{
    delete btnAbout;
    delete btnExit;
    delete btnStart;
    delete layout;

    startGame();
}
