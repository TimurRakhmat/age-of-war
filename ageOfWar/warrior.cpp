#include "warrior.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Warrior::Warrior(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    money_drop = 42;
    speed = 3;
    scale = 1;
    health = 700;
    maxHealth = health;
    currentFrame = 0;
    frameHeight = 36;

    frame_step = 22;
}

Warrior::~Warrior()
{
    delete atack;
    delete dead;
    delete idle;
    delete walk;
}

int Warrior::type() const
{
    return Type;
}

void Warrior::hit(int dmg)
{
    health -= dmg;
    if (health <= 0)
    {
        scene()->addItem(new Blood_smash(this->pos()));
        emit drop_money(money_drop);
        deleteLater();
    }
    update(0, -2, 2 * frame_step + 10, 2 * frameHeight + 5);
}

QRectF Warrior::boundingRect() const
{
    return QRectF(0, 0, dx, dy);
}

void Warrior::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, thatFrame->transformed(QTransform().scale(2 * scale, 2)), 2 * currentFrame, 0, 2 * frame_step, 2 * frameHeight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(0, -2, (int) dx*health/maxHealth, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Warrior::nextFrame()
{
    currentFrame += frame_step;
    if (currentFrame >= thatFrame->width())
        currentFrame = 0;
    update(0, -2, 2 * frame_step + 10, 2 * frameHeight + 5);
}

Skelet_rigth::Skelet_rigth() : Warrior()
{
    money_drop = 42;
    dmg = 4;

    dx = 22, dy = 32;

    speed = -3;
    scale = -1;

    atack = new QPixmap(":/image/skelet/Attack.png");
    dead = new QPixmap(":/image/skelet/Dead.png");
    idle = new QPixmap(":/image/skelet/Idle.png");
    walk = new QPixmap(":/image/skelet/Walk.png");

    thatFrame = walk;

    dx *= 2; dy *= 2;
}

int Skelet_rigth::type() const
{
    return Type;
}

void Skelet_rigth::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(0, 2)
                                                           << mapToScene(-10, 2));


    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 1)
        {
            thatFrame = atack;
            frame_step = 43;
            Warrior* temp = qgraphicsitem_cast <Warrior *> (item);
            temp->hit(randomBetween(dmg - 1, dmg + 1));
            return;
        }

        if (item->type() == UserType + 3)
        {
            thatFrame = atack;
            Player* temp = qgraphicsitem_cast <Player *> (item);
            temp->hit(randomBetween(dmg - 2, dmg));
            frame_step = 43;
            return;
        }

        if (item->type() == UserType + 2)
        {
            thatFrame = idle;
            frame_step = 24;
            return;;
        }
    }

    frame_step = 22;
    thatFrame = walk;
    this->setX(this->x() + speed);
}

Skelet_left::Skelet_left() : Warrior()
{
    money_drop = 42;
    dmg = 4;

    dx = 22, dy = 32;

    speed = 3;
    scale = 1;

    atack = new QPixmap(":/image/skelet/Attack.png");
    dead = new QPixmap(":/image/skelet/Dead.png");
    idle = new QPixmap(":/image/skelet/Idle.png");
    walk = new QPixmap(":/image/skelet/Walk.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}


int Skelet_left::type() const
{
    return Type;
}

void Skelet_left::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(dx, 0)
                                                           << mapToScene(dx, 2)
                                                           << mapToScene(dx + 10, 2));
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 2)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (item);
            temp->hit(randomBetween(dmg - 1, dmg + 1));
            thatFrame = atack;
            frame_step = 43;
            return;
        }

        if (item->type() == UserType + 4)
        {
            Player* temp = qgraphicsitem_cast <Player *> (item);
            temp->hit(randomBetween(dmg - 2, dmg));
            thatFrame = atack;
            frame_step = 43;
            return;
        }

        if (item->type() == UserType + 1)
        {
            thatFrame = idle;
            frame_step = 24;
            return;
        }
    }
    thatFrame = walk;
    frame_step = 22;
    this->setX(this->x() + speed);
}

Archer_left::Archer_left(): Warrior()
{
    money_drop = 60;
    health = 200;
    maxHealth = health;
    dmg = 6;
    speed = 3;

    frameHeight = 46;
    frame_step = 63;
    dx = 40, dy = 42;
    scale = 1;

    atack = new QPixmap(":/image/archer/attack.png");
    dead = new QPixmap(":/image/archer/dead.png");
    idle = new QPixmap(":/image/archer/idle.png");
    walk = new QPixmap(":/image/archer/walk.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}

int Archer_left::type() const
{
    return Type;
}

void Archer_left::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(dx, 0)
                                                           << mapToScene(dx, 20)
                                                           << mapToScene(dx + 140, 2));

    QGraphicsItem* temp_item;
    int min_dist = 2000;
    bool stop = false;

    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 2 || item->type() == UserType + 4)
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
        if (temp_item->type() == UserType + 2)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (temp_item);
            temp->hit(randomBetween(dmg - 2, dmg + 1));
        }
        else
        {
            Player* temp = qgraphicsitem_cast <Player *> (temp_item);
            temp->hit(randomBetween(dmg - 3, dmg));
        }

        if (!randomBetween(0, 8))
        scene()->addItem(new Arrow(QPointF(x() + dx, y() + dy * 0.45)));
        thatFrame = atack;
        frame_step = 63;
        return;
    }

    if (stop)
    {
        thatFrame = idle;
        frame_step = 63;
        return;
    }
    thatFrame = walk;
    frame_step = 63;
    this->setX(this->x() + speed);
}

Archer_right::Archer_right(): Warrior()
{
    money_drop = 60;
    health = 200;
    maxHealth = health;
    dmg = 6;
    speed = -3;

    frameHeight = 46;
    frame_step = 63;
    dx = 40, dy = 42;
    scale = -1;

    atack = new QPixmap(":/image/archer/attack.png");
    dead = new QPixmap(":/image/archer/dead.png");
    idle = new QPixmap(":/image/archer/idle.png");
    walk = new QPixmap(":/image/archer/walk.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}

int Archer_right::type() const
{
    return Type;
}

void Archer_right::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(0, 20)
                                                           << mapToScene(-140, 2));

    QGraphicsItem* temp_item;
    int min_dist = -200;
    bool stop = false;

    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 1 || item->type() == UserType + 3)
        {
            if (item->x() > min_dist)
            {
                min_dist = item->x();
                temp_item = item;
            }
        }

        if (item->type() == UserType + 2 && x() - item->x() < 50)
        {
            stop = true;
        }
    }

    if (min_dist > -200)
    {

        if (temp_item->type() == UserType + 1)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (temp_item);
            temp->hit(randomBetween(dmg - 2, dmg + 1));
        }
        else
        {
            Player* temp = qgraphicsitem_cast <Player *> (temp_item);
            temp->hit(randomBetween(dmg - 3, dmg));
        }

        if (!randomBetween(0, 8))
        scene()->addItem(new Arrow(QPointF(x(), y() + dy * 0.45) , false));

        thatFrame = atack;
        frame_step = 63;
        return;
    }

    if (stop)
    {
        thatFrame = idle;
        frame_step = 63;
        return;
    }

    thatFrame = walk;
    frame_step = 63;
    this->setX(this->x() + speed);
}

Knight_left::Knight_left(): Warrior()
{
    money_drop = 85;
    health = 900;
    maxHealth = health;
    dmg = 9;
    speed = 3;

    frameHeight = 42;
    frame_step = 42;
    dx = 22, dy = 42;
    scale = 1;

    atack = new QPixmap(":/image/knight/attack.png");
    dead = new QPixmap(":/image/knight/dead.png");
    idle = new QPixmap(":/image/knight/idle.png");
    walk = new QPixmap(":/image/knight/walk.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}

int Knight_left::type() const
{
    return Type;
}

void Knight_left::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(dx, 0)
                                                           << mapToScene(dx, 2)
                                                           << mapToScene(dx + 14, 2));
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 2)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (item);
            temp->hit(randomBetween(dmg - 1, dmg + 1));
            thatFrame = atack;
            frame_step = 80;
            return;
        }

        if (item->type() == UserType + 4)
        {
            Player* temp = qgraphicsitem_cast <Player *> (item);
            temp->hit(randomBetween(dmg - 2, dmg));
            thatFrame = atack;
            frame_step = 80;
            return;
        }

        if (item->type() == UserType + 1)
        {
            thatFrame = idle;
            frame_step = 42;
            return;
        }
    }
    thatFrame = walk;
    frame_step = 42;
    this->setX(this->x() + speed);
}


Knight_right::Knight_right(): Warrior()
{
    money_drop = 85;
    health = 900;
    maxHealth = health;
    dmg = 9;
    speed = -3;

    frameHeight = 42;
    frame_step = 42;
    dx = 22, dy = 42;
    scale = -1;

    atack = new QPixmap(":/image/knight/attack.png");
    dead = new QPixmap(":/image/knight/death.png");
    idle = new QPixmap(":/image/knight/idle.png");
    walk = new QPixmap(":/image/knight/walk.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}

int Knight_right::type() const
{
    return Type;
}

void Knight_right::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(0, 2)
                                                           << mapToScene(-14, 2));


    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 1)
        {
            thatFrame = atack;
            frame_step = 80;
            Warrior* temp = qgraphicsitem_cast <Warrior *> (item);
            temp->hit(randomBetween(dmg - 1, dmg + 1));
            return;
        }

        if (item->type() == UserType + 3)
        {
            thatFrame = atack;
            Player* temp = qgraphicsitem_cast <Player *> (item);
            temp->hit(randomBetween(dmg - 2, dmg));
            frame_step = 80;
            return;
        }

        if (item->type() == UserType + 2)
        {
            thatFrame = idle;
            frame_step = 42;
            return;;
        }
    }

    frame_step = 42;
    thatFrame = walk;
    this->setX(this->x() + speed);
}


Wizard_left::Wizard_left(): Warrior()
{
    money_drop = 115;
    health = 300;
    maxHealth = health;
    dmg = 8;
    speed = 3;

    frameHeight = 43;
    frame_step = 116;
    dx = 40, dy = 42;
    scale = 1;

    atack = new QPixmap(":/image/wizard/attack.png");
    dead = new QPixmap(":/image/wizard/death.png");
    idle = new QPixmap(":/image/wizard/idle.png");
    walk = new QPixmap(":/image/wizard/walk.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}

int Wizard_left::type() const
{
    return Type;
}

void Wizard_left::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(dx, 0)
                                                           << mapToScene(dx, 20)
                                                           << mapToScene(dx + 140, 2));

    QGraphicsItem* temp_item;
    int min_dist = 2000;
    bool stop = false;

    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 2 || item->type() == UserType + 4)
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
        if (temp_item->type() == UserType + 2)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (temp_item);
            temp->hit(randomBetween(dmg - 2, dmg + 1));
        }
        else
        {
            Player* temp = qgraphicsitem_cast <Player *> (temp_item);
            temp->hit(randomBetween(dmg - 3, dmg));
        }
        if (!randomBetween(0, 12))
            scene()->addItem(new MageBall(QPointF(x() + dx, y() + dy * 0.3)));
        thatFrame = atack;
        frame_step = 116;
        return;
    }

    if (stop)
    {
        thatFrame = idle;
        frame_step = 111;
        return;
    }
    thatFrame = walk;
    frame_step = 116;
    this->setX(this->x() + speed);
}


Wizard_right::Wizard_right(): Warrior()
{
    money_drop = 115;
    health = 300;
    maxHealth = health;
    dmg = 6;
    speed = -3;

    frameHeight = 43;
    frame_step = 116;
    dx = 40, dy = 42;
    scale = 1;

    atack = new QPixmap(":/image/wizard/attackrev.png");
    dead = new QPixmap(":/image/wizard/death.png");
    idle = new QPixmap(":/image/wizard/idlerev.png");
    walk = new QPixmap(":/image/wizard/walkrev.png");

    thatFrame = walk;
    dx *= 2; dy *= 2;
}

int Wizard_right::type() const
{
    return Type;
}

void Wizard_right::update_state()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(0, 20)
                                                           << mapToScene(-140, 2));

    QGraphicsItem* temp_item;
    int min_dist = -200;
    bool stop = false;

    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;

        if (item->type() == UserType + 1 || item->type() == UserType + 3)
        {
            if (item->x() > min_dist)
            {
                min_dist = item->x();
                temp_item = item;
            }
        }

        if (item->type() == UserType + 2 && x() - item->x() < 50)
        {
            stop = true;
        }
    }

    if (min_dist > -200)
    {

        if (temp_item->type() == UserType + 1)
        {
            Warrior* temp = qgraphicsitem_cast <Warrior *> (temp_item);
            temp->hit(randomBetween(dmg - 2, dmg + 1));
        }
        else
        {
            Player* temp = qgraphicsitem_cast <Player *> (temp_item);
            temp->hit(randomBetween(dmg - 3, dmg));
        }

        if (!randomBetween(0, 12))
            scene()->addItem(new MageBall(QPointF(x(), y() + dy * 0.3) , false));

        thatFrame = atack;
        frame_step = 116;
        return;
    }

    if (stop)
    {
        thatFrame = idle;
        frame_step = 111;
        return;
    }

    thatFrame = walk;
    frame_step = 116;
    this->setX(this->x() + speed);
}
