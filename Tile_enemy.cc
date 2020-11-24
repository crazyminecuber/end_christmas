#include "Tile.h"
#include "Tile_enemy.h"
//#include "Enemy.h"

void Tile_enemy::init()
{
    Tile::tiles[index_position] = this;
}

void Tile_enemy::set_direction(sf::Vector2f dir)
{
    direction = dir;
}

void Tile_enemy::update_enemy(Enemy* enemy)
{
    enemy->set_direction(direction);
}
//
// Tower* Tile_enemy::on_click()
// {
//     return nullprt;
// }
