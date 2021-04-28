#ifndef COMPUTER_H
#define COMPUTER_H


#include "player.h"
#include "warrior.h"

class Computer : public Player
{
    Q_OBJECT

    QTimer *brain_timer;

public:
    explicit Computer();
    ~Computer();
    enum { Type = UserType + 4};
    int type() const;
    void hit(int damage);

signals:

public slots:
    void stop();
    void resume();

    void brain_time_slot();
    void set_warrior();
    void set_archer();
};

#endif // COMPUTER_H
