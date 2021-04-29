#include "effects.h"

int fps = 25;
int cps = 80;

Blood_smash::Blood_smash(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setPos(point);
    this->setZValue(65);
    currentFrameX = 0;
    currentFrameY = 0;
    spriteImage = new QPixmap(":/image/blood.png");

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Blood_smash::nextFrame);
    timer->start(fps);
}

Blood_smash::~Blood_smash()
{
    delete spriteImage;
    delete timer;
}

QRectF Blood_smash::boundingRect() const
{
    return QRectF(-32, -48, 128, 128);
}

void Blood_smash::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-32, -48, *spriteImage, currentFrameX, currentFrameY, 128, 128);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Blood_smash::nextFrame()
{
    currentFrameX += 128;
    if (currentFrameX >= spriteImage->width() && currentFrameY >= spriteImage->height()) {
        this->deleteLater();
    } else {
        if (currentFrameX >= spriteImage->width())
        {
            currentFrameX = 0;
            currentFrameY += 128;
        }
    }
    this->update(-32, -48, 128, 128);
}

Arrow::Arrow(QPointF point, bool target)
{
    this->setPos(point);
    x0 = point.x();

    this->target = target;
    if (target)
        speed = 5;
    else
        speed = -5;

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Arrow::timeSlot);
    timer->start(fps);
}

Arrow::~Arrow()
{
    delete timer;
}

void Arrow::timeSlot()
{
    setPos(mapToParent(speed, 0));
    this->update(0, 0, 7, 2);
    if (qAbs(x() - x0) > 180)
        this->deleteLater();

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-1, -1)
                                                           << mapToScene(1, -1));

    foreach (QGraphicsItem *item, foundItems) {
        if ((item->type() == (UserType + 2) || item->type() == (UserType + 4)) && target){
            this->deleteLater();
            return;}
        if (((item->type() == (UserType + 1) || item->type() == (UserType + 3)) && !target)){
            this->deleteLater();
            return;}
        }
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,7,2);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Arrow::boundingRect() const
{
    return QRectF(0, 0, 7, 2);
}


MageBall::MageBall(QPointF point, bool target)
{
    this->setPos(point);
    x0 = point.x();

    this->target = target;
    if (target)
        speed = 5;
    else
        speed = -5;

    timer = new QTimer();   /// Инициализируем таймер анимации взрыва
    /// Подключаем сигнал от таймера к слоту анимации взрыва
    connect(timer, &QTimer::timeout, this, &MageBall::timeSlot);
    timer->start(fps);
}

MageBall::~MageBall()
{
    delete timer;
}

void MageBall::timeSlot()
{
    setPos(mapToParent(speed, 0));
    this->update(0, 0, 10, 10);
    if (qAbs(x() - x0) > 180)
        this->deleteLater();

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-1, -1)
                                                           << mapToScene(1, -1));

    foreach (QGraphicsItem *item, foundItems) {
        if ((item->type() == (UserType + 2) || item->type() == (UserType + 4)) && target){
            this->deleteLater();
            return;}
        if (((item->type() == (UserType + 1) || item->type() == (UserType + 3)) && !target)){
            this->deleteLater();
            return;}
        }
}

void MageBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::magenta);
    painter->drawEllipse(0,0,10,10);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF MageBall::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

ProgressBar::ProgressBar(QPointF point, int time)
{
    this->setPos(point);
    time0 = time;
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::timeSlot()
{
    time += cps;
    if (time >= time0)
    {
        emit end();
        deleteLater();
    }
    update(this->boundingRect());
}

void ProgressBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0,0,180,7);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    painter->drawRect(0,0, (int) 180 * time/time0,7);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF ProgressBar::boundingRect() const
{
    return QRectF(0, 0, 180, 7);
}
