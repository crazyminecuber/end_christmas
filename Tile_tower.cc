#include "Tile.h"
#include "Tile_tower.h"
using namespace std;

void Tile_tower::init()
{
    Tile::tiles[index_position] = this;
}

void Tile_tower::on_click(Tower * tw)
{
    cout << "checking out if tower is set" << endl;
    if (!(tw == nullptr))
    {
        cout << "Creating tower. Position: " << getPosition().x << " " << getPosition().y << endl;
        tw->create_active(getPosition() + sf::Vector2f{side_length / 2, side_length / 2});
    }
}

// bool Tile_tower::is_occupied()
// {
//     return  ( !(dynamic_cast<Tower_basic*> (tower) == nullptr) ||
//               !(dynamic_cast<Tower_ring* > (tower) == nullptr)   );
// }
