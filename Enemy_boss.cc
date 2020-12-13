#include <iostream>
#include <cstdlib>
#include "Entity.h"
#include "Enemy_boss.h"
#include "Projectile.h"


Enemy_boss::~Enemy_boss()
{
    //Spawn enemies upon death
    float mov_spd = death_child->get_movement_speed();
    for(int i = 0; i < num_of_children; i++)
    {
        Enemy* clone = death_child->clone();
        float mov_spd_factor = std::rand() % 100 + 1; //Value between 1-100
        //mov*fact, 1< new_mov_spd <1,5
        clone->set_movement_speed(mov_spd * (1 + (mov_spd_factor/200.f)));
        clone->setPosition(this->getPosition().x, this->getPosition().y);

        Enemy::create_enemy_by_obj(clone);
    }
}

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
Enemy* Enemy_boss::clone() const
{
    return new Enemy_boss{*this};
}
