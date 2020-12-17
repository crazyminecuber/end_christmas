#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Tile_tower.h"
using namespace std;

void Tile_tower::init()
{
    Tile::tiles[index_position] = this;
}

bool Tile_tower::on_click(Tower* tw)
{
    bool occupied{false};
    if ( !(tw == nullptr) )
    {
        tower = tw->create_active(getPosition()
                                    + sf::Vector2f{side_length / 2,
                                                   side_length / 2});
        occupied = true;
    }
    return occupied;
}

bool Tile_tower::is_occupied()
{
    return !(tower == nullptr);
}
