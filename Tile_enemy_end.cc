#include "Tile.h"
#include "Tile_enemy.h"
#include "Tile_enemy_end.h"

void Tile_enemy_end::update_enemy(Enemy* enemy)
{
    enemy->set_direction(direction);
}
