#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsObject>
#include "button.h"
#include "user.h"
#include "computer.h"
#include "warrior.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene *scene;
    QGraphicsItem *buttonParent;
    Button *exitBtn;
    Button *pauseBtn;
    Button *addWarrior;
    Button *addArcher;
    Button *addBArcher;
    Button *addKnight;
    QPixmap *game_bkgnd;
    QGraphicsPixmapItem *star;
    QGraphicsPixmapItem *coin;
    Warrior *warrior;
    Player *player1;
    Player *player2;
    QGraphicsTextItem* labelHealph;
    QGraphicsTextItem* labelExp;

    QGraphicsTextItem* labelWar;
    QGraphicsTextItem* labelArc;

public:
    GraphicsView(QMainWindow *parent);
    ~GraphicsView();

private:
    void setButton();
    void setLabel();

public slots:
    void exitSlot();
    void setWarrior();
    void setKnight();
    void setArcher();
    void setBArcher();
    void pause();

    void victoryExit();
    void defeatExit();

    void reset_money_lable(int);

signals:
    void exitSignal();
    void victory();
    void defeat();
};

#endif // GRAPHICSVIEW_H
