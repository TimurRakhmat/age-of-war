#include "warrior.h"

Warrior::Warrior(bool enemy, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    isEnemy = enemy;
    speed = enemy ? -2 : 2;
    scale = enemy ? -1 : 1;
    //enum { Type = UserType + 1};
    health = 1000;
    maxHealth = health;
    currentFrame = 0;
    frameHeight = 36;
    atack = new QPixmap(":/image/skelet/Attack.png");
    dead = new QPixmap(":/image/skelet/Dead.png");
    idle = new QPixmap(":/image/skelet/Idle.png");
    walk = new QPixmap(":/image/skelet/Walk.png");

    thatFrame = walk;
    ranga = 22;

    timer = new QTimer();   /// Инициализируем таймер анимации взрыва
    /// Подключаем сигнал от таймера к слоту анимации взрыва
    connect(timer, &QTimer::timeout, this, &Warrior::nextFrame);
    //connect(timer, &QTimer::timeout, this, &Warrior::update_state);
    timer->start(40);   /// Стартуем таймер с частотой 25 милисекунд
}

Warrior::~Warrior()
{
//    delete atack;
//    delete dead;
//    delete idle;
//    delete walk;
    delete timer;
}

void Warrior::hit()
{
    health -= 50;
    if (health <= 0)
        deleteLater();
}

QRectF Warrior::boundingRect() const
{
    return QRectF(0, 0,22,32);
}

void Warrior::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Отрисовываем один из кадров взрыва
    painter->drawPixmap(0, 0, thatFrame->transformed(QTransform().scale(scale, 1)), currentFrame, 0, ranga, 32);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(0, -2, (int) 21*health/maxHealth, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Warrior::nextFrame()
{
    currentFrame += ranga; // Продвигаем координату X для выбора следующего кадра
    if (currentFrame >= thatFrame->width())
        currentFrame = 0;
    update(0, -2, ranga, frameHeight);
}

Skelet::Skelet(bool enemy) : Warrior(enemy)
{

}


int Skelet::type() const
{
    return Type;
}

void Skelet::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(0, 2)
                                                           << mapToScene(-10, 2));
    //QList<QGraphicsItem *> foundItems = scene()->collidingItems(this);

    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 1)
        {
            speed = 0;
            thatFrame = atack;
            ranga = 43;
            Warrior* temp = qgraphicsitem_cast <Warrior *> (item);
            temp->hit();
            return;
        }

        if (item->type() == UserType + 3)
        {
            speed = 0;
            thatFrame = atack;
            Target* temp = qgraphicsitem_cast <Target *> (item);
            temp->hit(2);
            ranga = 43;
            return;
        }

        if (item->type() == UserType + 2)
        {
            speed = 0;
            thatFrame = idle;
            ranga = 24;
            return;;
        }
    }

    ranga = 22;
    thatFrame = walk;
    speed = -4;
    this->setX(this->x() + speed);
}

Skelet_left::Skelet_left(bool enemy) : Warrior(enemy)
{
}


int Skelet_left::type() const
{
    return Type;
}

void Skelet_left::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(22, 0)
                                                           << mapToScene(22, 2)
                                                           << mapToScene(32, 2));
    //QList<QGraphicsItem *> foundItems = scene()->collidingItems(this);
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 2)
        {
            speed = 0;
            Warrior* temp = qgraphicsitem_cast <Warrior *> (item);
            temp->hit();
            thatFrame = atack;
            ranga = 43;
            return;
        }

        if (item->type() == UserType + 3)
        {
            speed = 0;
            Target* temp = qgraphicsitem_cast <Target *> (item);
            temp->hit(2);
            thatFrame = atack;
            ranga = 43;
            return;
        }

        if (item->type() == UserType + 1)
        {
            speed = 0;
            thatFrame = idle;
            ranga = 24;
            return;
        }
    }

    speed = 4;
    thatFrame = walk;
    ranga = 22;
    this->setX(this->x() + speed);
}

Archer::Archer(bool enemy): Warrior(enemy)
{
    ranga = 63;
    health = 1500;
    maxHealth = 1500;
    frameHeight = 46;

    atack = new QPixmap(":/image/archer/attack.png");
    dead = new QPixmap(":/image/archer/dead.png");
    idle = new QPixmap(":/image/archer/idle.png");
    walk = new QPixmap(":/image/archer/walk.png");
}

int Archer::type() const
{
    return Type;
}

void Archer::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(40, 0)
                                                           << mapToScene(40, 20)
                                                           << mapToScene(180, 2));
    //QList<QGraphicsItem *> foundItems = scene()->collidingItems(this);

    QGraphicsItem* temp_item;
    int min_dist = 2000;
    bool stop = false;

    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 2 || item->type() == UserType + 3)
        {
            if (item->x() < min_dist)
            {
                min_dist = item->x();
                temp_item = item;
            }
        }

        if (item->type() == UserType + 1 && item->x() - x() < 50)
        {
            stop = true;
        }
    }

    if (min_dist < 2000)
    {

        speed = 0;
        if (temp_item->type() == UserType + 2)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (temp_item);
            temp->hit();
        }
        else
        {
            Target* temp = qgraphicsitem_cast <Target *> (temp_item);
            temp->hit(4);
        }
        thatFrame = atack;
        ranga = 63;
        return;
    }

    if (stop)
    {
        speed = 0;
        thatFrame = idle;
        ranga = 63;
        return;
    }

    speed = 4;
    thatFrame = walk;
    ranga = 63;
    this->setX(this->x() + speed);
}

void Archer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, thatFrame->transformed(QTransform().scale(scale, 1)), currentFrame, 0, ranga - 5, 42);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(0, -1, (int) 21*health/maxHealth, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Archer::boundingRect() const
{
    return QRect(0, 0, 40, 42);
}
