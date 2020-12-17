#include <iostream>
#include <cmath> // floor
#include "Tile.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"
#include "Tile_enemy_end.h"
using namespace std;

std::map<sf::Vector2i, Tile*, cmpTileByCoord> Tile::tiles;
float Tile::side_length{-1}; // gets calculated in Game::load_map

void Tile::init()
{
    /* sätt utseende */
    setTexture(texture, false);

    /* ge rätt storlek */
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(Tile::side_length / size_original.x,
             Tile::side_length / size_original.y);

    /* beräkna position */
    coord_position.x = index_position.x * Tile::side_length;
    coord_position.y = index_position.y * Tile::side_length;
    setPosition(coord_position);
}

Tile* Tile::get_tile_by_index(sf::Vector2i index)
{
    Tile* return_tile{nullptr};

    if (tiles.find(index) != tiles.end())
    {
        return_tile = tiles[index];
    }
    else
    {
        std::cout << "Error: could not find Tile at index ("
                  << index.x << ", " << index.y << ")" << endl;
    }

    return return_tile;
}

Tile* Tile::get_tile_by_coord(sf::Vector2f pos)
/* not reusing get_tile_by_coord to be able to have different error messages */
{
    int x = floor(pos.x / Tile::side_length);
    int y = floor(pos.y / Tile::side_length);
    sf::Vector2i index{x, y};
    Tile* return_tile{nullptr};

    if (tiles.find(index) != tiles.end())
    {
        return_tile = tiles[index];
    }
    else
    {
        std::cout << "Error: could not find Tile at position ("
                  << pos.x << ", " << pos.y << ")" << endl;
    }

    return return_tile;
}

Tile* Tile::get_tile_enemy_start()
{
    Tile* enemy_start = nullptr;
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin();
         it!=Tile::tiles.end(); ++it)
    {
        if ( is_tile_enemy_start((*it).first) )
            enemy_start = (*it).second;
    }
    return enemy_start;
}

Tile* Tile::get_tile_enemy_end()
{
    Tile* enemy_end = nullptr;
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin();
         it!=Tile::tiles.end(); ++it)
    {
        if ( is_tile_enemy_end((*it).first) )
            enemy_end = (*it).second;
    }
    return enemy_end;
}

bool Tile::is_tile_enemy(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

bool Tile::is_tile_enemy_start(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy_start*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

bool Tile::is_tile_enemy_end(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy_end*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

void Tile::update_side_length()
/* run this function if Tile::side_length is changed */
{
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(Tile::side_length / size_original.x,
             Tile::side_length / size_original.y);

    coord_position.x = index_position.x * Tile::side_length;
    coord_position.y = index_position.y * Tile::side_length;
    setPosition(coord_position);
}

sf::Vector2i Tile::get_index_position()
{
    return index_position;
}

int Tile::get_tile_number()
/* should never get used, only Tiles_enemy have tile_numbers */
{
    std::cout << "Error: trying to get tile_number from non-Tile_enemy"
              << std::endl;
    return -1;
}
