#ifndef TILE_ENEMY_H
#define TILE_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Enemy.h"

class Tile_enemy : public Tile
{
public:
    Tile_enemy(std::string texture_file,
               sf::Vector2i index_pos)
    : Tile(texture_file, index_pos)
    {}

    void set_direction(sf::Vector2f dir) override;
    bool ready_to_update_enemy(Enemy* enemy);
    virtual float update_enemy(Enemy* enemy) override;
    void set_tile_number(int tile_num) override;
    int get_tile_number() override;
    //Tower* on_click() override;

protected:
    sf::Vector2f direction{0, 0};
    int tile_number{-1}; // is set in Game::determine_tile_directions
};

#endif // TILE_ENEMY_H
