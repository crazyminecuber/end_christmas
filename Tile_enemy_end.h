#ifndef TILE_ENEMY_END_H
#define TILE_ENEMY_END_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Tile_enemy.h"
#include "Enemy.h"

class Tile_enemy_end : public Tile_enemy
{
public:
    Tile_enemy_end(std::string texture_file,
                   sf::Vector2i index_pos)
    : Tile_enemy(texture_file, index_pos)
    {}

    float update_enemy(Enemy* enemy) override;
};

#endif // TILE_ENEMY_END_H
