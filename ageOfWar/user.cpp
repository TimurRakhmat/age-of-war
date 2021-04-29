#include "user.h"
#include <QDebug>


User::User() :
    Player()
{
    warrior_cost = 40;
    money = 1000;
    archer_cost = 55;
}

User::~User()
{

}

int User::type() const
{
    return Type;
}

void User::add_warrior()
{
    add_time = true;
    Warrior* wars;
    if (tir == 1)
        wars = new Skelet_left();
    else
        wars = new Knight_left();
    connect(timer_update, &QTimer::timeout, wars, &Warrior::update_state);
    connect(timer_update_frame, &QTimer::timeout, wars, &Warrior::nextFrame);
    connect(wars, &Warrior::drop_money, this, &Player::unit_drop_money);
    scene()->addItem(wars);
    wars->setPos(x() + 150, y() + 165);
}

void User::add_archer()
{
    add_time = true;
    Warrior* wars;
    if (tir == 1)
        wars = new Archer_left();
    else
        wars = new Wizard_left();
    connect(timer_update, &QTimer::timeout, wars, &Warrior::update_state);
    connect(timer_update_frame, &QTimer::timeout, wars, &Warrior::nextFrame);
    connect(wars, &Warrior::drop_money, this, &Player::unit_drop_money);
    scene()->addItem(wars);
    wars->setPos(x() + 150, y() + 165);
}

void User::set_warrior()
{
    if (money < warrior_cost || !add_time)
        return;
    add_time = false;
    ProgressBar* bar = new ProgressBar(QPointF(0, this->y() - 20), warrior_set_time);
    scene()->addItem(bar);
    connect(timer_update, &QTimer::timeout, bar, &ProgressBar::timeSlot);
    connect(bar, &ProgressBar::end, this, &User::add_warrior);
    money -= warrior_cost;
}

void User::set_archer()
{
    if (money < archer_cost || !add_time)
        return;
    add_time = false;
    ProgressBar* bar = new ProgressBar(QPointF(0, this->y() - 20), warrior_set_time);
    scene()->addItem(bar);
    connect(timer_update, &QTimer::timeout, bar, &ProgressBar::timeSlot);
    connect(bar, &ProgressBar::end, this, &User::add_archer);
    money -= archer_cost;
}

