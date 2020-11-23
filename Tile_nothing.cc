#include "Tile.h"
#include "Tile_nothing.h"

void Tile_nothing::init()
{
    Tile::tiles[index_position] = this;
}

// Tower* Tile_nothing::on_click()
// {
//     return nullprt;
// }
