#include "Tile.h"
#include "Enemy.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"

float Tile_enemy_start::update_enemy(Enemy* enemy)
/* updates enemy movement and returns damage dealt to player */
{
    enemy->set_direction(direction);
    return 0;
}
