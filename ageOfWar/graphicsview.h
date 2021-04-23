#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsObject>
#include "button.h"
#include "target.h"
#include "warrior.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene *scene;
    QGraphicsItem *buttonParent;
    Button *exitBtn;
    Button *addWarrior;
    Button *addArcher;
    Button *addKnight;
    QPixmap *game_bkgnd;
    QPixmap skelet_image[4];
    Warrior *warrior;
    Target *target;
    Target *qtarget;
    QTimer *timer_set;
    QTimer *timer_update;
    QTimer *delay_timer;
    bool push_check;

public:
    GraphicsView(QMainWindow *parent);
    ~GraphicsView();

public slots:
    void exitSlot();
    void setWarrior();
    void setKnight();
    void setArcher();
    void delay_button();

signals:
    void exitSignal();
};

#endif // GRAPHICSVIEW_H
