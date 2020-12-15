#ifndef TILE_NOTHING_H
#define TILE_NOTHING_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Tile_nothing : public Tile
{
public:
    Tile_nothing(std::string texture_file,
                 sf::Vector2i index_pos)
    : Tile(texture_file, index_pos)
    {}

    //Tower* on_click() override;

};

#endif // TILE_NOTHING_H
