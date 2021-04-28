#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    timer_update = new QTimer();
    timer_update->start(cps);

    timer_update_frame = new QTimer();
    timer_update_frame->start(Fps);

    health = 1000;
    maxHealth = health;            // Устанавливаем максимальное здоровье равным текущему
    _pix = new QPixmap(":/image/Base.png");
}

Player::~Player()
{
    delete _pix;
    delete timer_update;
    delete timer_update_frame;
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0,180,200);   // Ограничиваем область, в которой лежит цель
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *_pix);

    //healph line
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, (int) 180*health/maxHealth, 8);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Player::hit(int damage)
{
    health -= damage;   // Уменьшаем здоровье мишени
    this->update(this->boundingRect());    // Перерисовываем мишень
    // Если здоровье закончилось, то инициируем смерть мишени
    if(health <= 0) {this->deleteLater();
    if (this->type() == UserType + 4)
        emit victory();
    else
        emit defeat();}

}

void Player::stop()
{
    timer_update->stop();
    timer_update_frame->stop();
}

void Player::resume()
{
    timer_update->start(cps);
    timer_update_frame->start(Fps);
}

void Player::unit_drop_money(int drop)
{
    emit unit_death(drop);
}

void Player::set_money(int coins)
{
    money += coins;
    exp += coins * 0.8;
}
