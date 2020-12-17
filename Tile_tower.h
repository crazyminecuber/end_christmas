#ifndef TILE_TOWER_H
#define TILE_TOWER_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Tile_tower : public Tile
{
public:
    Tile_tower(std::string texture_file,
               sf::Vector2i index_pos)
    : Tile(texture_file, index_pos)
    {
        init();
    }

    bool is_occupied();
    bool on_click(Tower * tw) override;
    void on_click(sf::Vector2f);
    void init();

private:
    Tower* tower{nullptr};
};

#endif // TILE_TOWER_H
