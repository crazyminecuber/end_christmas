#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite
{
public:
    Entity(std::string texture_file,
           sf::Vector2f position, sf::Vector2f size,
           float hit_rad, sf::Vector2f dir, float mov_spd)
    : sf::Sprite(),
    texture{Resource_manager::load(texture_file)}, size{size}, hitbox_radius{hit_rad}, direction{dir},
    movement_speed{mov_spd}
    {
        init(position);
    }
    Entity(Entity const & other)=default;
    virtual ~Entity(){};

    void init(sf::Vector2f position);

    float get_hitbox_radius() const;


protected:
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
