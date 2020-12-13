#include <iostream>
#include "Entity.h"
#include "Enemy_basic.h"

Enemy_basic::~Enemy_basic(){}


Enemy* Enemy_basic::clone() const
{
    return new Enemy_basic{*this};
}

bool Enemy_basic::collision(Projectile* object){
    life-= object->damage;
    if (life <= 0)
    {
      return true;
    }
    else
    {
      return false;
    }
}
