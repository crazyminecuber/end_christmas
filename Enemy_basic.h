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
        int arg_life)
    :Enemy(texture_file, position,
        size, hit_rad,
        dir, mov_spd,
        arg_life)
    {}

    ~Enemy_basic();

    //Statics
    static int life_init;
    static entity_properties prop;

    void collision(Entity* object);
    Enemy* clone() override;

};

#endif //ENEMY_BASIC_H
