#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "json.hpp" // to parse data from json file. See json.hpp for source.


#include "Resource_manager.h"
#include "Entity.h"
#include "Tile.h"
#include "Tile_nothing.h"
#include "Tile_tower.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"
#include "Tile_enemy_end.h"
using namespace std;
using json = nlohmann::json;
std::ostream& operator<<(std::ostream& output, sf::Vector2f const & vector);
std::ostream& operator<<(std::ostream& output, sf::Vector2i const & vector);

int const width  {1400};
int const height {800};
float Tile::side_length = 50;
std::map<std::string, sf::Texture> Resource_manager::resources;

void render();
void load_map(sf::RenderWindow const& window);
void render(sf::RenderWindow & window);
void determine_tile_directions();
bool is_tile_enemy(sf::Vector2i index);
bool is_tile_enemy_start(sf::Vector2i index);
bool is_tile_enemy_end(sf::Vector2i index);

int main()
{
    sf::RenderWindow window{sf::VideoMode{width, height}, "Tower defence"};
    load_map(window);

    while ( window.isOpen() )
    {
        render(window);
    }

    return 0;
}

void load_map(sf::RenderWindow const& window)
{
    /* förbered variabler för inläsning från fil */
    std::ifstream infile{"map.csv"};
    std::string line;
    int num;
    sf::Vector2i tile_index_pos(-1, -1);

    while ( std::getline(infile, line) )
    {
        tile_index_pos.x = -1;
        std::istringstream iss{line};
        while ( iss >> num )
        {
            if      ( num == -1 )
            {
                ;
            }
            else if ( num == 0 )
            {
                new Tile_nothing("stones.jpg", window, tile_index_pos);
            }
            else if ( num == 1 )
            {
                new Tile_tower("grass.jpg", window, tile_index_pos);
            }
            else if ( num == 2 )
            {
                new Tile_enemy("dirt.jpg", window, tile_index_pos);
            }
            else if ( num == 3 )
            {
                new Tile_enemy_start("dirt.jpg", window, tile_index_pos);
            }
            else if ( num == 4 )
            {
                new Tile_enemy_end("dirt.jpg", window, tile_index_pos);
            }
            else
            {
                cout << "Error: tile number not specified" << endl;
            }
            tile_index_pos.x++;
            iss.get();
        }
        tile_index_pos.y++;
    }
    cout << "Laddat in kartan" << endl;

    /* calculate Tile::side_length and change all tiles*/
    int tiles_per_row = tile_index_pos.y  + (1 - 2);
    int tiles_per_col = tile_index_pos.x + (1 - 2);
    Tile::side_length = std::min(width/tiles_per_row, height/tiles_per_col);

    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
    {
        (*it).second->update_side_length();
    }
    determine_tile_directions();
}

void determine_tile_directions()
{
    sf::Vector2i enemy_end;
    sf::Vector2i last_tile{-100, -100}; // init so never next to enemy_end
    sf::Vector2i current_tile;
    sf::Vector2i next_tile;
    sf::Vector2i direction;

    /* find enemy_end tile */
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
    {
        if ( is_tile_enemy_end((*it).first) )
            enemy_end = (*it).second->get_index_position();
    }
    cout << "Tile_enemy_end at: (" << enemy_end.x << ", " << enemy_end.y << ")" << endl;
    current_tile = enemy_end;

    /* loop through enemy path backwards and set set direction of tile */
    while ( !(is_tile_enemy_start(current_tile)) )
    {
        /* if (tile exists) and (tile is enemy) and (tile is not last tile) */
        // look up
        if ( Tile::tiles.find(current_tile + sf::Vector2i{0, -1})  !=
                Tile::tiles.end()                                  &&
             is_tile_enemy(  (current_tile + sf::Vector2i{0, -1})) &&
             last_tile !=    (current_tile + sf::Vector2i{0, -1})     )
        {
            next_tile = current_tile + sf::Vector2i{0, -1};
        }
        // look right
        if ( Tile::tiles.find(current_tile + sf::Vector2i{1, 0})  !=
                Tile::tiles.end()                                 &&
             is_tile_enemy(  (current_tile + sf::Vector2i{1, 0})) &&
             last_tile !=    (current_tile + sf::Vector2i{1, 0})     )
        {
            next_tile = current_tile + sf::Vector2i{1, 0};
        }
        // look down
        if ( Tile::tiles.find(current_tile + sf::Vector2i{0, 1})  !=
                Tile::tiles.end()                                 &&
             is_tile_enemy(  (current_tile + sf::Vector2i{0, 1})) &&
             last_tile !=    (current_tile + sf::Vector2i{0, 1})     )
        {
            next_tile = current_tile + sf::Vector2i{0, 1};
        }
        // look left
        if ( Tile::tiles.find(current_tile + sf::Vector2i{-1, 0})  !=
                Tile::tiles.end()                                  &&
             is_tile_enemy(  (current_tile + sf::Vector2i{-1, 0})) &&
             last_tile !=    (current_tile + sf::Vector2i{-1, 0})     )
        {
            next_tile = current_tile + sf::Vector2i{-1, 0};
        }

        // prepare for next iteration
        last_tile = current_tile;
        current_tile = next_tile;

        // set direction
        direction = last_tile - current_tile;
        Tile::get_tile_by_index(current_tile)->set_direction(direction);
    }
}

bool is_tile_enemy(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

bool is_tile_enemy_start(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy_start*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

bool is_tile_enemy_end(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy_end*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

void render(sf::RenderWindow & window)
{
    window.clear();
    for (auto it{begin(Tile::tiles)}; it != end(Tile::tiles); ++it)
    {
        window.draw(*it->second);
    }
    window.display();
}

/* overload stream operator för sf::Vector2f */
std::ostream& operator<<(std::ostream& output, sf::Vector2f const & vector)
{
    output << "(" << vector.x << ", " << vector.y << ")";
    return output;
}

/* overload stream operator för sf::Vector2i */
std::ostream& operator<<(std::ostream& output, sf::Vector2i const & vector)
{
    output << "(" << vector.x << ", " << vector.y << ")";
    return output;
}
