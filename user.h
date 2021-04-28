#ifndef USER_H
#define USER_H

#include "player.h"
#include "warrior.h"

class User : public Player
{
    Q_OBJECT
public:
    User();
    ~User();
    enum { Type = UserType + 3};
    int type() const;
    void hit(int damage);

    int warrior_set_time = 2000;
    int archer_set_time = 2500;

private:
    void add_warrior();
    void add_archer();

    bool add_time = true;

signals:

public slots:
    void set_warrior();
    void set_archer();
};

#endif // USER_H
