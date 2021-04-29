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
    Button *addArcher;
    Button *addKnight;

    Button *tirUpgr;

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
    void setKnight();
    void setArcher();
    void pause();

    void victoryExit();
    void defeatExit();

    void reset_tir_label();
    void reset_money_lable(int);
    void set_tir_btn();

signals:
    void exitSignal();
    void victory();
    void defeat();
};

#endif // GRAPHICSVIEW_H
