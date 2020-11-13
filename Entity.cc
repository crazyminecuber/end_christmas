#include "Entity.h"

void Entity::init(std::string texture_file, sf::Vector2f position)
{
    /* sätt utseende */
    sf::Texture texture;
    texture.loadFromFile(texture_file);
    setTexture(texture, false);
    // ge rätt storlek
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(size.x / size_original .x, size.y / size_original.y);

    setPosition(position);
    setOrigin(size.x/2.f, size.y/2.f);
}
