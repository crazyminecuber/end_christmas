#ifndef TILE_TOWER_H
#define TILE_TOWER_H

#include <SFML/Graphics.hpp>
#include <string>
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

    void init();
    bool on_click(Tower* tw) override;
    void on_right_click(sf::Vector2f);
    bool is_occupied();

private:
    Tower* tower{nullptr};
};

#endif // TILE_TOWER_H
