#include "Entity.h"
#include "Resource_manager.h"
#include <iostream> // debugg

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
