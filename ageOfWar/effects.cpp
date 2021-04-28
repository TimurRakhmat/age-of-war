#include "effects.h"

int fps = 25;
int cps = 80;

Blood_smash::Blood_smash(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setPos(point);    // Устанавливаем позицию взрыва
    currentFrameX = 0;
    currentFrameY = 0;
    spriteImage = new QPixmap(":/image/blood.png");

    timer = new QTimer();   /// Инициализируем таймер анимации взрыва
    /// Подключаем сигнал от таймера к слоту анимации взрыва
    connect(timer, &QTimer::timeout, this, &Blood_smash::nextFrame);
    timer->start(fps);   /// Стартуем таймер с частотой 25 милисекунд
}

Blood_smash::~Blood_smash()
{
    delete spriteImage;
    delete timer;
}

QRectF Blood_smash::boundingRect() const
{
    return QRectF(0, 0, 1, 1);
}

void Blood_smash::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Отрисовываем один из кадров взрыва
    painter->drawPixmap(0, -48, *spriteImage, currentFrameX, currentFrameY, 96, 96);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Blood_smash::nextFrame()
{
    currentFrameX += 96; // Продвигаем координату X для выбора следующего кадра
    if (currentFrameX >= spriteImage->width() && currentFrameY >= spriteImage->height()) {
        this->deleteLater();    // Если кадры закончились, то удаляем объект взрыва
    } else {
        if (currentFrameX >= spriteImage->width())
        {
            currentFrameX = 0;
            currentFrameY += 96;
        }    // В противном случае обновляем графический объект
    }
    this->update(0, -48, 96, 96);
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

    timer = new QTimer();   /// Инициализируем таймер анимации взрыва
    /// Подключаем сигнал от таймера к слоту анимации взрыва
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
    this->update(0, 0, 7, 1);
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
    painter->drawRect(0,0,7,1);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Arrow::boundingRect() const
{
    return QRectF(0, 0, 7, 1);
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
