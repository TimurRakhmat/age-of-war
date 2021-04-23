#include "target.h"

Target::Target(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    health = 1000;
    maxHealth = health;            // Устанавливаем максимальное здоровье равным текущему
    _pix = new QPixmap(":/image/Base.png");
}

Target::~Target()
{
    delete _pix;
}

int Target::type() const
{
    return Type;
}

QRectF Target::boundingRect() const
{
    return QRectF(0, 0,180,200);   // Ограничиваем область, в которой лежит цель
}

void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *_pix);

    /* Отрисовываем полоску жизни
     * соизмеримо текущему здоровью
     * относительно максимального здоровья
     * */
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, (int) 180*health/maxHealth, 8);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Target::hit(int damage)
{
    health -= damage;   // Уменьшаем здоровье мишени
    this->update(this->boundingRect());    // Перерисовываем мишень
    // Если здоровье закончилось, то инициируем смерть мишени
    if(health <= 0) this->deleteLater();
}
