#include <string>
#include <ostream>
#include "Entity.h"
#include "Resource_manager.h"
#include <iostream> // debugg
#include <cmath> // abs
#include "Tile.h"

std::ostream& operator<<(std::ostream& os,const Entity & E)
{
    os  << "Entity at position : ("
        << std::to_string(E.getPosition().x) << ", "
        << std::to_string(E.getPosition().y);
    return os;
}
/* Beware that size, hitbox_radius, movement_speed will be scaled with
 * Tile::side_length.
 */
Entity::Entity(std::string _texture_file,
        sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd)
: sf::Sprite(),
    texture_file{_texture_file},
    texture{Resource_manager::load(_texture_file)},
    size{(siz*Tile::side_length)},
    hitbox_radius{(hit_rad*Tile::side_length)},
    direction{dir},
    movement_speed{(mov_spd*Tile::side_length)}
{
    init(position);
}

void Entity::init(sf::Vector2f position)
{
    /* Sets texture */
    setTexture(texture, false);

    setOrigin(getGlobalBounds().width / 2.f, getGlobalBounds().height / 2.f);

    // fixs size
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(size.x / size_original.x, size.y / size_original.y);
    scale_moving_right = getScale();

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

float Entity::get_movement_speed() const
{
    return movement_speed;
}

void Entity::set_movement_speed(float mov_spd)
{
    movement_speed = mov_spd;
}

std::string Entity::get_texture_file() const
{
    return texture_file;
}

void Entity::flip(sf::Vector2f dir)
{
    if ( abs(dir.x) > 0.5 ) // if moving left or right
    {
        setScale((scale_moving_right.x * dir.x), scale_moving_right.y);
    }
}
