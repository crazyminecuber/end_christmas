#include <iostream>
#include "Entity.h"
#include "Enemy_boss.h"
#include "Projectile.h"


// Ska skapa flera enemy_basic
Enemy_boss::~Enemy_boss(){}

//Overloada collision för olika object?
bool Enemy_boss::collision(Projectile* object){
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


//Statics
int Enemy_boss::life_init;
entity_properties Enemy_boss::prop;
