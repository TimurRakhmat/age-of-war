#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Target : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Target(QObject *parent = 0);
    ~Target();
    enum { Type = UserType + 3};
    int type() const;
    void hit(int damage);

signals:

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int health;         // Текущий запас здоровья мишени
    int maxHealth;      // Максимальный запас здоровья мишени
    QPixmap* _pix;
};

#endif // TARGET_H
