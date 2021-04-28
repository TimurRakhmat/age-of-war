#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include <QDebug>

const int cps = 40;
const int Fps = 30;

class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Player(QObject *parent = 0);
    ~Player();

    virtual int type() const = 0;
    void hit(int damage);
    virtual void stop();
    virtual void resume();

    int warrior_cost;
    int archer_cost;
    int money = 500;
    int exp = 0;

signals:
    void unit_death(int);
    void victory();
    void defeat();
    void tir_upgrade();

public slots:
    virtual void set_warrior() = 0;
    virtual void set_archer() = 0;

    void unit_drop_money(int);
    void set_money(int coins);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QTimer *timer_update;
    QTimer *timer_update_frame;
    int health;
    int maxHealth;
    QPixmap* _pix;
};
#endif // PLAYER_H
