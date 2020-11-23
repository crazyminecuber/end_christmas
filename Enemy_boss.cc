#include <iostream>
#include "Entity.h"
#include "Enemy_boss.h"

// Ska skapa flera enemy_basic
Enemy_boss::~Enemy_boss(){}

//Overloada collision för olika object?
void Enemy_boss::collision(Entity* object){
    std::cout << "krockat" << object << std::endl;
}


//Statics
int Enemy_boss::life_init;
entity_properties Enemy_boss::prop;
