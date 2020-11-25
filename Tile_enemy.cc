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
    bool ready_check{false};
    // moving right
    if ( enemy->get_direction() == sf::Vector2f{1, 0} )
    {
        if ( (enemy->getPosition().x + (enemy->getGlobalBounds().width / 2)) >
             (coord_position.x       + (Tile::side_length / 2))                )
        {
            ready_check = true;
        }
    }
    // moving left
    else if ( enemy->get_direction() == sf::Vector2f{-1, 0} )
    {
        if ( (enemy->getPosition().x + (enemy->getGlobalBounds().width / 2)) <
             (coord_position.x       + (Tile::side_length / 2))                )
        {
            ready_check = true;
        }
    }
    // moving up
    else if ( enemy->get_direction() == sf::Vector2f{0, -1} )
    {
        if ( (enemy->getPosition().y + (enemy->getGlobalBounds().height / 2)) <
             (coord_position.y       + (Tile::side_length / 2))                )
        {
            ready_check = true;
        }
    }
    // moving down
    else if ( enemy->get_direction() == sf::Vector2f{0, 1} )
    {
        if ( (enemy->getPosition().y + (enemy->getGlobalBounds().height / 2)) >
             (coord_position.y       + (Tile::side_length / 2))                )
        {
            ready_check = true;
        }
    }

    return ready_check;
}

//
// Tower* Tile_enemy::on_click()
// {
//     return nullprt;
// }
