#include <iostream> // debugg
#include "Tile.h"
#include "Entity.h"
#include "Enemy.h"
#include "Tile_enemy.h"
#include "Tile_enemy_end.h"

float Tile_enemy_end::update_enemy(Enemy* enemy)
{
    float damage_dealt{0};
    if ( ready_to_update_enemy(enemy) )
    {
        enemy->set_direction(direction);
        damage_dealt = enemy->get_damage();
    }
    return damage_dealt;
}
