#include "Tile.h"
#include "Tile_tower.h"

void Tile_tower::init()
{
    Tile::tiles[index_position] = this;
}

// bool Tile_tower::is_occupied()
// {
//     return  ( !(dynamic_cast<Tower_basic*> (tower) == nullptr) ||
//               !(dynamic_cast<Tower_ring* > (tower) == nullptr)   );
// }
//
// Tower* Tile_tower::on_click()
// {
//     return tower;
// }
