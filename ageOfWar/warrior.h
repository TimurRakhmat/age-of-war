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
    explicit Warrior(bool enemy = false, QObject *parent = 0);
    ~Warrior();

    virtual int type() const = 0;
    void hit(int);

signals:
    void drop_money(int);

public slots:
    virtual void update_state() = 0;
    void nextFrame();   /// Слот для перелистывания кадров

private:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
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
    bool isEnemy;
    int speed;
    int dmg;
    int frameHeight;
    int scale;
    int currentFrame;
};

class Skelet : public Warrior
{
    Q_OBJECT
public:
    explicit Skelet(bool enemy = false);
    int type() const;

    enum { Type = UserType + 2 };

public slots:   /// Слот для перелистывания кадров
    void update_state();
};

class Skelet_left : public Warrior
{
    Q_OBJECT
public:
    explicit Skelet_left(bool enemy = false);
    int type() const;

    /* Переопределяем тип Графического объекта взрыва,
     * чтобы пуля могла данный объект игнорировать
     * */
    enum { Type = UserType + 1 };
   /// Координата текущего кадра в спрайте

public slots:
    void update_state();
};

class Archer : public Warrior
{
    Q_OBJECT
public:
    explicit Archer(bool enemy = false);
    int type() const;

    /* Переопределяем тип Графического объекта взрыва,
     * чтобы пуля могла данный объект игнорировать
     * */
    enum { Type = UserType + 1 };
   /// Координата текущего кадра в спрайте

public slots:
    void update_state();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

class Archer_right : public Warrior
{
    Q_OBJECT
public:
    explicit Archer_right(bool enemy = false);
    int type() const;

    /* Переопределяем тип Графического объекта взрыва,
     * чтобы пуля могла данный объект игнорировать
     * */
    enum { Type = UserType + 2 };
   /// Координата текущего кадра в спрайте

public slots:
    void update_state();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // WARRIOR_H
