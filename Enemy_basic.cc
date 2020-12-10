#include <iostream>
#include "Entity.h"
#include "Enemy_basic.h"

Enemy_basic::~Enemy_basic(){}


Enemy* Enemy_basic::clone(){
    return new Enemy_basic{*this};
}

//Statics
int Enemy_basic::life_init;
int Enemy_basic::reward_init;
entity_properties Enemy_basic::prop;



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
