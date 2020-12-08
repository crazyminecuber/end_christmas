#include <iostream>
#include "Entity.h"
#include "Enemy_boss.h"
#include "Projectile.h"


// Ska skapa flera enemy_basic
Enemy_boss::~Enemy_boss(){}

//Overloada collision för olika object?
bool Enemy_boss::collision(Projectile* object){
    std::cout << "krockat" << *object << std::endl;
<<<<<<< HEAD
    life -= object->damage;
=======
    life-= object->damage;
>>>>>>> 9a99dbe386b730e1b77e01fa5c3c88941ed2ecc9
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
