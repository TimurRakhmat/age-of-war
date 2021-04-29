#ifndef WARRIOR_H
#define WARRIOR_H

#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include "effects.h"
#include "player.h"


class Warrior : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Warrior(QObject *parent = 0);
    ~Warrior();

    virtual int type() const = 0;
    void hit(int);

signals:
    void drop_money(int);

public slots:
    virtual void update_state() = 0;
    void nextFrame();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    int health;
    int maxHealth;

    int money_drop;

    int frame_step;

    QPixmap *walk = nullptr;
    QPixmap *atack = nullptr;
    QPixmap *idle = nullptr;
    QPixmap *dead = nullptr;
    QPixmap *thatFrame = walk;

    int dx, dy;

    int speed;
    int dmg;
    int frameHeight;
    int scale;
    int currentFrame;
};


class Skelet_rigth : public Warrior
{
    Q_OBJECT
public:
    explicit Skelet_rigth();
    int type() const;

    enum { Type = UserType + 2 };

public slots:
    void update_state();
};


class Skelet_left : public Warrior
{
    Q_OBJECT
public:
    explicit Skelet_left();
    int type() const;
    enum { Type = UserType + 1 };

public slots:
    void update_state();
};


class Archer_left : public Warrior
{
    Q_OBJECT
public:
    explicit Archer_left();
    int type() const;
    enum { Type = UserType + 1 };

public slots:
    void update_state();

};


class Archer_right : public Warrior
{
    Q_OBJECT
public:
    explicit Archer_right();
    int type() const;
    enum { Type = UserType + 2 };

public slots:
    void update_state();
};


class Wizard_left : public Warrior
{
    Q_OBJECT
public:
    explicit Wizard_left();
    int type() const;
    enum { Type = UserType + 1 };

public slots:
    void update_state();

};


class Wizard_right : public Warrior
{
    Q_OBJECT
public:
    explicit Wizard_right();
    int type() const;
    enum { Type = UserType + 2 };

public slots:
    void update_state();
};


class Knight_left : public Warrior
{
    Q_OBJECT
public:
    explicit Knight_left();
    int type() const;
    enum { Type = UserType + 1 };

public slots:
    void update_state();
};

class Knight_right : public Warrior
{
    Q_OBJECT
public:
    explicit Knight_right();
    int type() const;
    enum { Type = UserType + 2 };

public slots:
    void update_state();
};

#endif // WARRIOR_H
