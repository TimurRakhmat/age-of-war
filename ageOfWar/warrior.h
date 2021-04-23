#ifndef WARRIOR_H
#define WARRIOR_H

#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include "target.h"

class Warrior : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Warrior(bool enemy = false, QObject *parent = 0);
    ~Warrior();

    virtual int type() const = 0;
    void hit();

signals:

public slots:
    virtual void update_state() = 0;

protected slots:
    void nextFrame();   /// Слот для перелистывания кадров

private:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    int health;         // Текущий запас здоровья мишени
    int maxHealth;
    int ranga;
    QTimer *timer;  /// Таймер для анимации взрыва

    QPixmap *walk;
    QPixmap *atack;
    QPixmap *idle;
    QPixmap *dead;
    QPixmap *thatFrame;
    bool isEnemy;
    int speed;
    int frameHeight;
    int scale;
    int currentFrame;   /// Координата текущего кадра в спрайте
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

#endif // WARRIOR_H
