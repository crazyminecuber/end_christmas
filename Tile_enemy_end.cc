#include <iostream> // debugg
#include "Tile.h"
#include "Entity.h"
#include "Tile_enemy.h"
#include "Tile_enemy_end.h"

float Tile_enemy_end::update_enemy(Enemy* enemy)
{
    enemy->set_direction(direction);
    float damage_dealt = enemy->get_damage();
    return damage_dealt;
}
