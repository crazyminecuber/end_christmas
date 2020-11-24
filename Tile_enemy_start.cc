#include "Tile.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"

void Tile_enemy_start::update_enemy(Enemy* enemy)
{
    enemy->set_direction(direction);
}
