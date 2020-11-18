#include <iostream>
#include "Entity.h"
#include "Enemy_basic.h"

Enemy_basic::~Enemy_basic(){}

void Enemy_basic::collision(Entity* object){
    std::cout << "krockat" << object << std::endl;
}
