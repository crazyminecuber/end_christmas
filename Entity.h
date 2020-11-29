#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Resource_manager.h"

class Entity : public sf::Sprite
{
public:
    Entity(std::string _texture_file,
           sf::Vector2f position, sf::Vector2f size,
           float hit_rad, sf::Vector2f dir, float mov_spd)
    : sf::Sprite(), texture_file{_texture_file},
    texture{Resource_manager::load(_texture_file)}, size{size}, hitbox_radius{hit_rad}, direction{dir},
    movement_speed{mov_spd}
    {
        init(position);
    }
    Entity(Entity const & other)=default;
    virtual ~Entity()=default;

    void init(sf::Vector2f position);

    float get_hitbox_radius() const;


protected:
    std::string texture_file;
    sf::Texture texture;
    sf::Vector2f size; //Ska den vara Vector2u och inte Vector2f?
    float hitbox_radius;
public:
    sf::Vector2f direction;
    float const movement_speed;
};

struct entity_properties{
    std::string texture_file;
    sf::Vector2f size;
    float hit_rad;
    sf::Vector2f dir;
    float mov_spd;
};

#endif //ENTITY_H
