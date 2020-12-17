#include "Tile.h"
#include "Tile_enemy.h"
#include "Tile_enemy_end.h"
#include "Enemy.h"

float Tile_enemy_end::update_enemy(Enemy* enemy)
/* updates enemy movement and returns damage dealt to player*/
{
    float damage_dealt{0};
    if ( has_passed_middle(enemy) )
    {
        enemy->set_direction(direction);
        damage_dealt = enemy->get_damage();
    }
    return damage_dealt;
}
