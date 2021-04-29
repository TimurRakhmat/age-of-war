#include "graphicsview.h"
#include <QDebug>


GraphicsView::GraphicsView(QMainWindow *parent): QGraphicsView(parent)
{
    qsrand(time(0));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "AgeOfWar"));
    this->setGeometry(parent->geometry());
    show();
    this->setSceneRect(this->geometry());
    game_bkgnd = new QPixmap(":/image/bckg.jpg");
    this->setBackgroundBrush(game_bkgnd->scaled(this->size(), Qt::IgnoreAspectRatio));

    scene = new QGraphicsScene;
    scene->setSceneRect(this->geometry());
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    this->setScene(scene);
    this->setRenderHint(QPainter::Antialiasing);

    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    player1 = new User();  // Создаём цель
    scene->addItem(player1);
    player1->setPos(0, parent->height() - 270);
    player2 = new Computer();  // Создаём цель
    scene->addItem(player2);
    player2->setPos(parent->width() - 180, parent->height() - 270);

    connect(player2, &Player::victory, this, &GraphicsView::victoryExit);
    connect(player1, &Player::defeat, this, &GraphicsView::defeatExit);

    connect(player1, &Player::unit_death, player2, &Player::set_money);
    connect(player2, &Player::unit_death, player1, &Player::set_money);

    connect(player2, &Player::unit_death, this, &GraphicsView::reset_money_lable);

    connect(player1, &Player::tir_upgrade, this, &GraphicsView::set_tir_btn);

    setLabel();
    setButton();
}

GraphicsView::~GraphicsView()
{
    delete game_bkgnd;
    scene->deleteLater();
}

void GraphicsView::setButton()
{
    buttonParent = new QGraphicsRectItem;

    exitBtn = new Button(QPixmap(":/image/menu.png"), buttonParent);
    connect(exitBtn, &Button::pressed, this, &GraphicsView::exitSlot);
    exitBtn->setPos(0, 0);

    addKnight = new Button(QPixmap(":/image/skelet/Skeleton.png"), buttonParent);
    connect(addKnight, &Button::pressed, this, &GraphicsView::setKnight);
    addKnight->setPos(-100, 0);

    labelWar = new QGraphicsTextItem(buttonParent);
    labelWar->setDefaultTextColor(QColor(44, 28, 36));
    QFont font=QFont("Arial", 12, QFont::Bold);
    labelWar->setFont(font);
    QString text = QString::number(player1->warrior_cost);
    labelWar->setPlainText(text);
    labelWar->setPos(-110, 20);

    addArcher = new Button(QPixmap(":/image/archer/icon.png"), buttonParent);
    connect(addArcher, &Button::pressed, this, &GraphicsView::setArcher);
    addArcher->setPos(-200, 0);

    labelArc = new QGraphicsTextItem(buttonParent);
    labelArc->setDefaultTextColor(QColor(44, 28, 36));
    font=QFont("Arial", 12, QFont::Bold);
    labelArc->setFont(font);
    text = QString::number(player1->archer_cost);
    labelArc->setPlainText(text);
    labelArc->setPos(-210, 20);

    scene->addItem(buttonParent);
    buttonParent->setPos(width() - 100, 50);
    buttonParent->setZValue(65);
}

void GraphicsView::setLabel()
{
    coin = scene->addPixmap(QPixmap(":/image/gold.png"));
    coin->setPos(0, 0);

    labelHealph = new QGraphicsTextItem();
    labelHealph->setDefaultTextColor(QColor(44, 28, 36));
    QFont font=QFont("Arial", 12, QFont::Bold);
    labelHealph->setFont(font);
    QString text = QString::number(player1->money);
    labelHealph->setPlainText(text);

    labelHealph->setPos(100, 0);
    scene->addItem(labelHealph);

    star = scene->addPixmap(QPixmap(":/image/star.png"));
    star->setPos(0, 100);

    labelExp = new QGraphicsTextItem();
    labelExp->setDefaultTextColor(QColor(44, 28, 36));
    QFont font2=QFont("Arial", 12, QFont::Bold);
    labelExp->setFont(font2);
    QString text2 = QString::number(player1->exp);
    labelExp->setPlainText(text2);

    labelExp->setPos(100, 100);
    scene->addItem(labelExp);
}

void GraphicsView::setKnight()
{
    player1->set_warrior();
    QString text = QString::number(player1->money);
    labelHealph->setPlainText(text);
}

void GraphicsView::setArcher()
{
    player1->set_archer();
    QString text = QString::number(player1->money);
    labelHealph->setPlainText(text);
}

void GraphicsView::pause()
{
    QWidget* Form = new QWidget;
    Form->setAttribute(Qt::WA_DeleteOnClose, true);
    Form->show();
    player1->stop();
    player2->stop();
}

void GraphicsView::victoryExit()
{
    emit victory();
}

void GraphicsView::defeatExit()
{
    emit defeat();
}

void GraphicsView::reset_tir_label()
{
    QString text = QString::number(player1->archer_cost);
    labelArc->setPlainText(text);

    text = QString::number(player1->warrior_cost);
    labelWar->setPlainText(text);

    addArcher->set_pixmap(QPixmap(":/image/wizard/icon.png"));
    addKnight->set_pixmap(QPixmap(":/image/knight/icon.png"));
    addKnight->update(addKnight->boundingRect());
    addArcher->update(addArcher->boundingRect());
    sender()->deleteLater();
}

void GraphicsView::reset_money_lable(int)
{
    QString text = QString::number(player1->money);
    labelHealph->setPlainText(text);
    text = QString::number(player1->exp);
    labelExp->setPlainText(text);
}

void GraphicsView::set_tir_btn()
{
    tirUpgr = new Button(QPixmap(":/image/star.png"), buttonParent);
    connect(tirUpgr, &Button::pressed, player1, &Player::set_tir);
    connect(tirUpgr, &Button::pressed, this, &GraphicsView::reset_tir_label);
    //connect(tirUpgr, &Button::pressed, tirUpgr, &Button::deleteLater);
    tirUpgr->setPos(-1600, 100);
}

void GraphicsView::exitSlot()
{
    if (player1 != nullptr)
        player1->stop();
    if (player2 != Q_NULLPTR)
        player2->stop();

    QMessageBox msgBox;
    // Заголовок сообщения
    msgBox.setText("Pause");

    msgBox.addButton("menu", QMessageBox::RejectRole);
    msgBox.addButton("resume", QMessageBox::AcceptRole);

    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::AcceptRole:
         emit exitSignal();
         break;
      case QMessageBox::RejectRole:
        {
        if (player1)
        player1->resume();
        if (player2)
        player2->resume();
        }
    }

}
