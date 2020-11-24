#ifndef TILE_ENEMY_START_H
#define TILE_ENEMY_START_H

#include <SFML/Graphics.hpp>
#include "Tile_enemy.h"
#include "Enemy.h"

class Tile_enemy_start : public Tile_enemy
{
public:
    Tile_enemy_start(std::string texture_file, sf::RenderWindow const& win,
               sf::Vector2i index_pos)
    : Tile_enemy(texture_file, win, index_pos)
    {}

    void update_enemy(Enemy* enemy) override {};
};

#endif // TILE_ENEMY_START_H
