#include <iostream>
#include "Entity.h"
#include "Enemy_boss.h"

Enemy_boss::~Enemy_boss(){}

void Enemy_boss::collision(Entity* object){
    std::cout << "krockat" << object << std::endl;
}
