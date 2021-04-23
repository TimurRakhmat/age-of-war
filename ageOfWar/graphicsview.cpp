#include "graphicsview.h"
#include <QDebug>

GraphicsView::GraphicsView(QMainWindow *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(QRect(0, 0, 1890, 1030));
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    delay_timer = new QTimer();
    push_check = true;
    connect(delay_timer, &QTimer::timeout, this, &GraphicsView::delay_button);

//    skelet_image[0] = QPixmap(":/image/skelet/Attack");
//    skelet_image[1] = QPixmap(":/image/skelet/Dead");
//    skelet_image[2] = QPixmap(":/image/skelet/Idle");
//    skelet_image[3] = QPixmap(":/image/skelet/Walk");


    buttonParent = new QGraphicsRectItem;
    exitBtn = new Button(QPixmap(":/image/menu.png"), buttonParent);
    connect(exitBtn, &Button::pressed, this, &GraphicsView::exitSlot);
    exitBtn->setPos(0, 0);

    addWarrior = new Button(QPixmap(":/image/skelet/Skeleton.png"), buttonParent);
    connect(addWarrior, &Button::pressed, this, &GraphicsView::setWarrior);
    addWarrior->setPos(-100, 0);

    addKnight = new Button(QPixmap(":/image/skelet/Skeleton.png").transformed(QTransform().scale(-1, 1)), buttonParent);
    connect(addKnight, &Button::pressed, this, &GraphicsView::setKnight);
    addKnight->setPos(-200, 0);

    addArcher = new Button(QPixmap(":/image/archer/icon.png").transformed(QTransform().scale(-1, 1)), buttonParent);
    connect(addArcher, &Button::pressed, this, &GraphicsView::setArcher);
    addArcher->setPos(-300, 0);

    scene->addItem(buttonParent);
    buttonParent->setPos(parent->width() - 100, 50);
    buttonParent->setZValue(65);

    target = new Target();  // Создаём цель
    scene->addItem(target);
    target->setPos(0, parent->height() - 370);
    qtarget = new Target();  // Создаём цель
    scene->addItem(qtarget);
    qtarget->setPos(parent->width() - 180, parent->height() - 370);

    timer_set = new QTimer();
    //connect(timer_set, &QTimer::timeout, this, &GraphicsView::setWarrior);
    //connect(timer_set, &QTimer::timeout, this, &GraphicsView::setKnight);
    timer_set->start(4500);

    timer_update = new QTimer();
    timer_update->start(100);

    this->setScene(scene);
    this->setRenderHint(QPainter::Antialiasing);

    game_bkgnd = new QPixmap(":/image/Background.png");
    this->setBackgroundBrush(game_bkgnd->scaled(parent->size(), Qt::IgnoreAspectRatio));

    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    this->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "AgeOfWar"));
    this->setGeometry(parent->geometry());
    this->showFullScreen();
}

GraphicsView::~GraphicsView()
{
    delete game_bkgnd;
    scene->deleteLater();
}

void GraphicsView::setKnight()
{
//    if (!push_check)
//        return;
//    push_check = false;
//    delay_timer->start(1000);

    warrior = new Skelet_left();
    connect(timer_update, &QTimer::timeout, warrior, &Warrior::update_state);
    warrior->setPos(target->x() + 180, target->y() + 185);
    scene->addItem(warrior);
}

void GraphicsView::setArcher()
{
    warrior = new Archer();
    connect(timer_update, &QTimer::timeout, warrior, &Warrior::update_state);
    warrior->setPos(target->x() + 180, target->y() + 185);
    scene->addItem(warrior);
}

void GraphicsView::delay_button()
{
    push_check = true;
}

void GraphicsView::exitSlot()
{
    emit exitSignal();
}

void GraphicsView::setWarrior()
{
    warrior = new Skelet(true);
    connect(timer_update, &QTimer::timeout, warrior, &Warrior::update_state);
    warrior->setPos(qtarget->x() - 30, qtarget->y() + 185);
    scene->addItem(warrior);
}
