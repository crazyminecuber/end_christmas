#include <iostream> //debugg
#include <cmath>
#include "Tile.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"
#include "Tile_enemy_end.h"
using namespace std;

std::map<sf::Vector2i, Tile*, cmpTileByCoord> Tile::tiles;
float Tile::side_length{-1}; // changes automatically in Game::load_map


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
    int x = floor(pos.x / Tile::side_length);
    int y = floor(pos.y / Tile::side_length);
    sf::Vector2i index{x, y};
    if (tiles.find(index) != tiles.end())
    {
        return tiles[index];
    }
    return nullptr;
}

Tile* Tile::get_tile_by_index(sf::Vector2i index)
{
    return tiles[index];
}

Tile* Tile::get_tile_enemy_start()
{
    Tile* enemy_start = nullptr;
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
    {
        if ( is_tile_enemy_start((*it).first) )
            enemy_start = (*it).second;
    }
    return enemy_start;
}

Tile* Tile::get_tile_enemy_end()
{
    Tile* enemy_end = nullptr;
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
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

void Tile::set_direction(sf::Vector2f dir)
{
    dir = sf::Vector2f{0, 0}; // compiler don't likes "unused arguments"
}

float Tile::update_enemy(Enemy* enemy)
{
    enemy->direction.x += 0; // compiler don't likes "unused arguments"
    return 0;
}

void Tile::set_tile_number(int tile_num)
{
    tile_num; // compiler don't likes "unused arguments"
}

int Tile::get_tile_number()
{
    return 0;
}
