#ifndef TILE_NOTHING_H
#define TILE_NOTHING_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Tile_nothing : public Tile
{
public:
    Tile_nothing(std::string texture_file, sf::RenderWindow const& win,
                 sf::Vector2i index_pos)
    : Tile(texture_file, win, index_pos)
    {
        init();
    }

    //Tower* on_click() override;

private:
    void init();
};

#endif // TILE_NOTHING_H
