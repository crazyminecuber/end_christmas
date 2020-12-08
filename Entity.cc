#include <string>
#include <ostream>
#include "Entity.h"
#include "Resource_manager.h"

std::ostream& operator<<(std::ostream& os,const Entity & E)
{
    os << "Entity at position : (" 
        << std::to_string(E.getPosition().x) << ", " 
        << std::to_string(E.getPosition().y);
    return os;
}
void Entity::init(sf::Vector2f position)
{
    /* sätt utseende */
    setTexture(texture, false);
    // ge rätt storlek
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(size.x / size_original .x, size.y / size_original.y);

    setPosition(position);
    setOrigin(size.x/2.f, size.y/2.f);
}

float Entity::get_hitbox_radius() const
{
    return hitbox_radius;
}
