#ifndef ENEMY_BASIC_H
#define ENEMY_BASIC_H

#include "Entity.h"
#include "Enemy.h"

class Enemy_basic
: public Enemy
{
public:
    Enemy_basic(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int arg_life, int reward_init)
    :Enemy(texture_file, position,
        size, hit_rad,
        dir, mov_spd,
        arg_life, reward_init)
    {}

    ~Enemy_basic();
    
    Enemy* clone() const override;
    bool   collision(Projectile* object) override;

};

#endif //ENEMY_BASIC_H
