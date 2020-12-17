#ifndef ENTITY_H
#define ENTITY_H

#include "Resource_manager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Entity : public sf::Sprite
{
public:
    Entity(std::string _texture_file,
           sf::Vector2f position, sf::Vector2f size,
           float hit_rad, sf::Vector2f dir, float mov_spd);
    virtual ~Entity()=default;

    void init(sf::Vector2f position);

    sf::Vector2f get_direction();
    void set_direction(sf::Vector2f dir);
    void flip(sf::Vector2f dir);
    float get_hitbox_radius() const;
    std::string get_texture_file() const;
    float get_movement_speed() const;
    void  set_movement_speed(float mov_spd);


protected:
    std::string texture_file;
    sf::Texture texture;
    sf::Vector2f size;
    sf::Vector2f scale_moving_right; // used when flipping to remember which direction is right
    float hitbox_radius;
public:
    sf::Vector2f direction;
    float movement_speed;
};

struct entity_properties{
    std::string texture_file;
    sf::Vector2f size;
    float hit_rad;
    sf::Vector2f dir;
    float mov_spd;
};
std::ostream& operator<<(std::ostream& os,const Entity & E);
#endif //ENTITY_H
