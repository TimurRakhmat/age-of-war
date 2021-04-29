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
    _pix1 = new QPixmap(":/image/Base.png");
    _pix2 = new QPixmap(":/image/Base2.png");
    _pix = _pix1;
}

Player::~Player()
{
    delete _pix1;
    delete _pix2;
    delete timer_update;
    delete timer_update_frame;
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0,180,200);
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
    health -= damage;
    this->update(this->boundingRect());

    if(health <= 0) {
        this->deleteLater();
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
    if (tir == 1 && exp >= expToUprgade)
    {
        if (this->type() == UserType + 4)
            set_tir();
        else
            emit tir_upgrade();
    }
}

void Player::set_tir()
{
    tir = 2;
    warrior_cost = 90;
    archer_cost = 110;
    _pix = _pix2;
    update(this->boundingRect());
}
