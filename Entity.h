#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite
{
public:
    Entity(std::string texture_file,
           sf::Vector2f position, sf::Vector2f siz,
           float hit_rad, sf::Vector2f dir, float mov_spd)
    : sf::Sprite(),
    size{siz}, hitbox_radius{hit_rad}, direction{dir}, movement_speed{mov_spd}
    {
        init(texture_file, position);
    }

    void init(std::string texture_file, sf::Vector2f position);

protected:
    sf::Vector2u size;
    float hitbox_radius;
    sf::Vector2f direction;
    float const movement_speed;
};

#endif //ENTITY_H
