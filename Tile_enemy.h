#ifndef TILE_ENEMY_H
#define TILE_ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"
#include "Enemy.h"

class Tile_enemy : public Tile
{
public:
    Tile_enemy(std::string texture_file,
               sf::Vector2i index_pos)
    : Tile(texture_file, index_pos)
    {}

    virtual float update_enemy(Enemy* enemy) override;
    bool has_passed_middle(Enemy* enemy);
    void set_direction(sf::Vector2f dir) override;
    void set_tile_number(int tile_num) override;
    int  get_tile_number() override;

protected:
    sf::Vector2f direction{0, 0}; // is set in Game::determine_tile_directions
    int tile_number{-1}; // is set in Game::determine_tile_directions
};

#endif // TILE_ENEMY_H
