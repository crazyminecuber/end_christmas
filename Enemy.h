#ifndef ENEMY_H
#define ENEMY_H

//TODO Make test for making instance
#include <vector>
#include "Entity.h"

class Enemy
: public Entity
{
public:
    Enemy(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int arg_life)
    :Entity(texture_file, position,
        size, hit_rad,
        dir, mov_spd),
        life{arg_life}{}

    static std::vector<Enemy*> enemies;

    protected:
        int life;
};

#endif //ENEMY_H
