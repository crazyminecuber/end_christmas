#include "Tile.h"
#include "Tile_tower.h"
using namespace std;

void Tile_tower::init()
{
    Tile::tiles[index_position] = this;
}

bool Tile_tower::on_click(Tower * tw)
{
    cout << "checking out if tower is set" << endl;
    if (!(tw == nullptr))
    {
        cout << "Creating tower. Position: " << getPosition().x << " " << getPosition().y << endl;
        tower = tw->create_active(getPosition() + sf::Vector2f{side_length / 2, side_length / 2});

        return true;
    }
    return false;
}

bool Tile_tower::is_occupied()
{
    cout << "Tower in tile" << tower << endl;
    return !(tower == nullptr);
}
