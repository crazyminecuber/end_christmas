#ifndef ENEMY_BOSS_H
#define ENEMY_BOSS_H

#include "Enemy.h"

class Enemy_boss
: public Enemy
{
public:
    Enemy_boss()
    : Enemy()
    {}
    ~Enemy_boss();
private:
  //Någon function som kallas av destruktorn som skapar basics

};

#endif //ENEMY_BOSS_H
