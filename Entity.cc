#include <string>
#include <ostream>
#include "Entity.h"
#include "Resource_manager.h"
#include <iostream> // debugg

std::ostream& operator<<(std::ostream& os,const Entity & E)
{
    os << "Entity at position : ("
        << std::to_string(E.getPosition().x) << ", "
        << std::to_string(E.getPosition().y);
    return os;
}
//void Entity::init(sf::Vector2f position)
void Entity::init(sf::Vector2f position, sf::Vector2f size)
{
    /* sätt utseende */
    setTexture(texture, false);

    setOrigin(getGlobalBounds().width / 2.f, getGlobalBounds().height / 2.f);

    // ge rätt storlek
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(size.x / size_original.x, size.y / size_original.y);

    setPosition(position);
}

float Entity::get_hitbox_radius() const
{
    return hitbox_radius;
}

void Entity::set_direction(sf::Vector2f dir)
{
    direction = dir;
}

sf::Vector2f Entity::get_direction()
{
    return direction;
}
std::string Entity::get_texture_file() const
{
    return texture_file;
}
