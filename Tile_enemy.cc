#include "Tile_enemy.h"
#include "Tile.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream> //debugg

void Tile_enemy::set_direction(sf::Vector2f dir)
{
    direction = dir;
}

float Tile_enemy::update_enemy(Enemy* enemy)
/* updates enemy movement and returns damage dealt to player*/
{
    if ( has_passed_middle(enemy) )
    {
        enemy->set_direction(direction);
        enemy->flip(direction);
    }
    return 0;
}

bool Tile_enemy::has_passed_middle(Enemy* enemy)
/* checks if an enemy has passed the middle of its current tile,
   different checks depending on enemy direction                */
{
    bool ready_check{false};
    // moving right
    if ( enemy->get_direction() == sf::Vector2f{1, 0} )
    {
        if ( (enemy->getPosition().x) >
             (coord_position.x       + (Tile::side_length / 2)) )
        {
            ready_check = true;
        }
    }
    // moving left
    else if ( enemy->get_direction() == sf::Vector2f{-1, 0} )
    {
        if ( (enemy->getPosition().x) <
             (coord_position.x       + (Tile::side_length / 2)) )
        {
            ready_check = true;
        }
    }
    // moving up
    else if ( enemy->get_direction() == sf::Vector2f{0, -1} )
    {
        if ( (enemy->getPosition().y) <
             (coord_position.y       + (Tile::side_length / 2)) )
        {
            ready_check = true;
        }
    }
    // moving down
    else if ( enemy->get_direction() == sf::Vector2f{0, 1} )
    {
        if ( (enemy->getPosition().y) >
             (coord_position.y       + (Tile::side_length / 2)) )
        {
            ready_check = true;
        }
    }
    // standing still
    else if ( enemy->get_direction() == sf::Vector2f{0, 0} )
    {
        ready_check = true;
    }

    return ready_check;
}

void Tile_enemy::set_tile_number(int tile_num)
{
    tile_number = tile_num;
}

int Tile_enemy::get_tile_number()
{
    return tile_number;
}
