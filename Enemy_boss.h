#ifndef ENEMY_BOSS_H
#define ENEMY_BOSS_H

#include "Entity.h"
#include "Enemy.h"

class Enemy_boss
: public Enemy
{
public:
    Enemy_boss(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int arg_life, int reward_init, int num_of_child, Enemy* child)
    :Enemy(texture_file, position,
        size, hit_rad,
        dir, mov_spd,
        arg_life, reward_init),
        num_of_children{num_of_child},death_child{child}{}

    ~Enemy_boss();

    bool collision(Projectile* object);
    Enemy* clone() const override;

protected:
    int num_of_children;
    Enemy* death_child;

};

#endif //ENEMY_BOSS_H
