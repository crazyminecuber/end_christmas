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
        //Every enemy needs it's own instance
        Enemy* clone = death_child->clone();

        //The new movement speed will be between, 1< mov_spd <1,5
        //The difference in movement speed is used to separate the
        //enemies when a big group spawns.
        float mov_spd_factor = std::rand() % 100 + 1; //Value between 1-100
        clone->set_movement_speed(mov_spd * (1 + (mov_spd_factor/200.f)));
        clone->setPosition(this->getPosition().x, this->getPosition().y);

        Enemy::create_enemy_by_obj(clone);
    }
    delete death_child;
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
    //Deep copy
    Enemy* child = death_child->clone();
    Enemy_boss* clone = new Enemy_boss{*this};
    clone->death_child = child;
    return clone;
}

void Enemy_boss::prep_passive_removal()
{
  num_of_children = 0;
}