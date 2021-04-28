#include "computer.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

int Cps = 3400;

Computer::Computer() :
    Player()
{
    money = 400;
    warrior_cost = 40;
    archer_cost = 55;
    brain_timer = new QTimer();
    connect(brain_timer, &QTimer::timeout, this, &Computer::brain_time_slot);
    brain_timer->start(Cps);
}

Computer::~Computer()
{

}

int Computer::type() const
{
    return Type;
}


void Computer::hit(int damage)
{
    health -= damage;   // Уменьшаем здоровье мишени
    this->update(this->boundingRect());    // Перерисовываем мишень
    // Если здоровье закончилось, то инициируем смерть мишени
    if(health <= 0) this->deleteLater();
}

void Computer::stop()
{
    brain_timer->stop();
    timer_update->stop();
    timer_update_frame->stop();
}

void Computer::resume()
{
    brain_timer->start(Cps);
    timer_update->start(cps);
    timer_update_frame->start(Fps);
}

void Computer::brain_time_slot()
{
    int ch = randomBetween(1, 3);

    if (ch < 3)
        set_warrior();
    else
        set_archer();
}

void Computer::set_warrior()
{
    if (money < warrior_cost)
        return;
    money -= warrior_cost;
    Warrior* wars = new Skelet(true);
    connect(timer_update, &QTimer::timeout, wars, &Warrior::update_state);
    connect(timer_update_frame, &QTimer::timeout, wars, &Warrior::nextFrame);
    connect(wars, &Warrior::drop_money, this, &Player::unit_drop_money);
    wars->setPos(x() - 20, y() + 185);
    scene()->addItem(wars);
}

void Computer::set_archer()
{
    if (money < warrior_cost)
        return;
    money -= archer_cost;
    Warrior* wars = new Archer_right(true);
    connect(timer_update, &QTimer::timeout, wars, &Warrior::update_state);
    connect(timer_update_frame, &QTimer::timeout, wars, &Warrior::nextFrame);
    connect(wars, &Warrior::drop_money, this, &Player::unit_drop_money);
    wars->setPos(x() - 20, y() + 185);
    scene()->addItem(wars);
}

