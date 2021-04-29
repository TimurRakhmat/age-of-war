#ifndef EFFECTS_H
#define EFFECTS_H


#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>
#include <QPainter>


// blood spray after unit death
class Blood_smash : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Blood_smash(QPointF point, QObject *parent = 0);
    ~Blood_smash();

signals:

public slots:

private slots:
    void nextFrame();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QTimer *timer;
    QPixmap *spriteImage;
    int currentFrameX;
    int currentFrameY;
};


//class arrow for archer attack
class Arrow : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Arrow(QPointF point, bool target = true);
    ~Arrow();

signals:

public slots:

private slots:
    void timeSlot();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int speed;
    int x0;
    bool target;
    QTimer *timer;

};


//class arrow for archer attack
class MageBall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MageBall(QPointF point, bool target = true);
    ~MageBall();

signals:

public slots:

private slots:
    void timeSlot();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int speed;
    int x0;
    bool target;
    QTimer *timer;

};

// make unit progress bar
class ProgressBar : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ProgressBar(QPointF point, int time);
    ~ProgressBar();

signals:
    void end();

public slots:
    void timeSlot();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int time = 0;
    int time0;
    QTimer *timer;

};

#endif // EFFECTS_H
