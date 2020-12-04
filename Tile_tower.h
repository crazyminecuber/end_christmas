#ifndef TILE_TOWER_H
#define TILE_TOWER_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Tile_tower : public Tile
{
public:
    Tile_tower(std::string texture_file, sf::RenderWindow const& win,
               sf::Vector2i index_pos)
    : Tile(texture_file, win, index_pos)
    {
        init();
    }

    //bool is_occupied();
    void on_click(Tower * tw) override;

private:
    void init();
    //Tower* tower{nullptr};
};

#endif // TILE_TOWER_H
