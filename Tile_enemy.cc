#include "Tile.h"
#include "Entity.h"
#include "Tile_enemy.h"
#include <iostream> //debugg
//#include "Enemy.h"

void Tile_enemy::init()
{
    Tile::tiles[index_position] = this;
}

void Tile_enemy::set_direction(sf::Vector2f dir)
{
    direction = dir;
}

float Tile_enemy::update_enemy(Enemy* enemy)
{
    if ( ready_to_update_enemy(enemy) )
    {
        enemy->set_direction(direction);
    }
    return 0;
}

bool Tile_enemy::ready_to_update_enemy(Enemy* enemy)
{
    // moving right
    if ( enemy->get_direction() == sf::Vector2f{1, 0} )
    {
        if ( (enemy->getPosition().x + (enemy->getGlobalBounds().width / 2)) >
             (coord_position.x       + (Tile::side_length / 2))                )
        {
            return true;
        }
    }
    return false;
}

//
// Tower* Tile_enemy::on_click()
// {
//     return nullprt;
// }
