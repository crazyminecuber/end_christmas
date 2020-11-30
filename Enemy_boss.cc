#include <iostream>
#include "Entity.h"
#include "Enemy_boss.h"
#include "Projectile.h"


// Ska skapa flera enemy_basic
Enemy_boss::~Enemy_boss(){}

//Overloada collision för olika object?
bool Enemy_boss::collision(Projectile* object){
    std::cout << "krockat" << *object << std::endl;
    life_init-= object->damage;
    if (life_init <= 0)
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
