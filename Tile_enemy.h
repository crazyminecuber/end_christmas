#ifndef TILE_ENEMY_H
#define TILE_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Enemy.h"

class Tile_enemy : public Tile
{
public:
    Tile_enemy(std::string texture_file, sf::RenderWindow const& win,
               sf::Vector2i index_pos)
    : Tile(texture_file, win, index_pos)
    {
        init();
    }

    void set_direction(sf::Vector2f dir) override;
    virtual float update_enemy(Enemy* enemy);
    //Tower* on_click() override;

protected:
    void init();
    sf::Vector2f direction{0, 0};
};

#endif // TILE_ENEMY_H
