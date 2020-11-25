#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <unordered_map> // kanske ändra till unordered_map?
#include "Resource_manager.h"
#include "Enemy.h"

struct cmpTileByCoord;

class Tile : public sf::Sprite
{
public:
    Tile(std::string texture_file, sf::RenderWindow const& win,
         sf::Vector2i index_pos)
    : sf::Sprite(),
    window{win}, texture{Resource_manager::load(texture_file)},
    index_position{index_pos}
    {
        init();
    }

    void init();
    void update_side_length();
    sf::Vector2i get_index_position();
    //virtual Tower* on_click() {};
    virtual void set_direction(sf::Vector2f dir);
    virtual float update_enemy(Enemy* enemy);


    /* static members and functions */
    static std::map<sf::Vector2i, Tile*, cmpTileByCoord> tiles;
    static float side_length;
    static Tile* get_tile_by_coord(sf::Vector2f coord_pos);
    static Tile* get_tile_by_index(sf::Vector2i index);
    static Tile* get_tile_enemy_start();
    static Tile* get_tile_enemy_end();
    static bool is_tile_enemy(sf::Vector2i index);
	static bool is_tile_enemy_start(sf::Vector2i index);
	static bool is_tile_enemy_end(sf::Vector2i index);

protected:
    sf::RenderWindow const& window;
    sf::Texture const& texture;
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
