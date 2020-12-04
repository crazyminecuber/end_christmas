#include <iostream>
#include "Entity.h"
#include "Enemy_basic.h"

//Statics
int Enemy_basic::life_init;
entity_properties Enemy_basic::prop;

Enemy_basic::~Enemy_basic(){}

bool Enemy_basic::collision(Projectile* object){
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
