#include <iostream> //debugg
#include "Tile.h"

std::map<sf::Vector2i, Tile*, cmpTileByCoord> Tile::tiles;

void Tile::init()
{
    /* sätt utseende */
    setTexture(texture, false);
    // ge rätt storlek
    sf::Vector2u size_original;
    size_original = texture.getSize();
    setScale(Tile::side_length / size_original.x,
             Tile::side_length / size_original.y);

    // beräkna position
    coord_position.x = index_position.x * Tile::side_length;
    coord_position.y = index_position.y * Tile::side_length;
    setPosition(coord_position);
}

Tile* Tile::get_tile_by_coord(sf::Vector2f pos)
{
    int row = pos.x / Tile::side_length;
    int col = pos.y / Tile::side_length;
    sf::Vector2i index{row, col};
    return tiles[index];
}

Tile* Tile::get_tile_by_index(sf::Vector2i index)
{
    return tiles[index];
}

void Tile::update_side_length()
{
    /* run this function if Tile::side_length is changed */
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
