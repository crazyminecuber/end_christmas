#include "Tile.h"
#include "Entity.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"
#include <iostream> // debugg

float Tile_enemy_start::update_enemy(Enemy* enemy)
{
    std::cout << "här är jag" << std::endl;
    enemy->set_direction(direction);
    return 0;
}
