#include <iostream>
#include "Entity.h"
#include "Enemy_basic.h"

Enemy_basic::~Enemy_basic(){}



void Enemy_basic::collision(Entity* object){
    std::cout << "krockat" << *object << std::endl;
}


//Statics
int Enemy_basic::life_init;
entity_properties Enemy_basic::prop;
