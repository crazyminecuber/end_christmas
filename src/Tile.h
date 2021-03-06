#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Resource_manager.h"
#include "Enemy.h"
#include "Tower.h"

struct cmpTileByCoord;

class Tile : public sf::Sprite
{
public:
    Tile(std::string texture_file,
         sf::Vector2i index_pos)
    : sf::Sprite(),
    texture{Resource_manager::load(texture_file)},
    index_position{index_pos}
    {
        init();
    }

    void          init();
    void          update_side_length();
    sf::Vector2i  get_index_position();
    virtual bool  on_click(Tower*){return false;};
    virtual void  set_direction(sf::Vector2f){};
    virtual float update_enemy(Enemy*){return 0;};
    virtual void  set_tile_number(int){};
    virtual int   get_tile_number();

    /* static members and functions */
    static std::map<sf::Vector2i, Tile*, cmpTileByCoord> tiles;
    static float side_length;
    static Tile* get_tile_by_coord(sf::Vector2f coord_pos);
    static Tile* get_tile_by_index(sf::Vector2i index);
    static Tile* get_tile_enemy_start();
    static Tile* get_tile_enemy_end();
    static bool  is_tile_enemy(sf::Vector2i index);
	static bool  is_tile_enemy_start(sf::Vector2i index);
	static bool  is_tile_enemy_end(sf::Vector2i index);

protected:
    sf::Texture  const& texture;
    sf::Vector2f coord_position;
    sf::Vector2i index_position;
};

struct cmpTileByCoord
/* sort Vector2i by row and then column */
{
    bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const
    {
        if ( a.y == b.y )
            return a.x < b.x;
        else
            return a.y < b.y;
    }
};

#endif //TILE_H
