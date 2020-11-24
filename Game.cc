#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include "json.hpp" // to parse data from json file. See json.hpp for source.

#include "Game.h"
#include "Enemy_basic.h"
#include "Enemy_boss.h"
#include "Projectile.h"
#include "Entity.h"
#include "Tower.h"
#include "Resource_manager.h"
#include "Tile.h"
#include "Tile_nothing.h"
#include "Tile_tower.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"
#include "Tile_enemy_end.h"

using namespace std;
using json = nlohmann::json;
float Tile::side_length = 50; // flytta

// Help function to determine init projectile for tower
// Projectile* Game::get_tower_projectile(std::string const & projectile)
// {
//     if(projectile == "Projectile_basic")
//     {
//         return new Projectile_basic{};
//     }
//     else if(projectile == "Projectile_pierce")
//     {
//         return new Projectile_pierce{};
//     }
//     else if(projectile == "Projectile_bomb")
//     {
//         return new Projectile_bomb{};
//     }
// }

// // Help function to determine if object1 and object2 have collided
// bool Game::collided(Entity const *object1, Entity const *object2)
// {
//     return (pow(object1->getPosition().x - object2->getPosition().x,2)
//             < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
//             && pow(object1->getPosition().y - object2->getPosition().y,2)
//             < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
//            );
// }

void Game::load_map(string const & file) //use file "map.csv"
{
    /* prepare variables needed for reading from file */
    std::ifstream infile{file};
    std::string line;
    int num;
    sf::Vector2i tile_index_pos(-1, -1);

    /* create all tiles */
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
                new Tile_nothing("resources/textures/stones.jpg", window, tile_index_pos);
            }
            else if ( num == 1 )
            {
                new Tile_tower("resources/textures/grass.jpg", window, tile_index_pos);
            }
            else if ( num == 2 )
            {
                new Tile_enemy("resources/textures/dirt.jpg", window, tile_index_pos);
            }
            else if ( num == 3 )
            {
                new Tile_enemy_start("resources/textures/dirt.jpg", window, tile_index_pos);
            }
            else if ( num == 4 )
            {
                new Tile_enemy_end("resources/textures/dirt.jpg", window, tile_index_pos);
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
    // infile.close();
    cout << "Laddat in kartan" << endl;

    /* update side_length */
    // calculate Tile::side_length and change all tiles
    int tiles_per_row = tile_index_pos.y  + (1 - 2);
    int tiles_per_col = tile_index_pos.x + (1 - 2);
    Tile::side_length = std::min(window_width/tiles_per_row, window_height/tiles_per_col);
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
    {
        (*it).second->update_side_length();
    }

    /* set direction of tiles */
    determine_tile_directions();
}

void Game::determine_tile_directions()
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
    // cout << "Tile_enemy_end at: (" << enemy_end.x << ", " << enemy_end.y << ")" << endl;
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

bool Game::is_tile_enemy(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

bool Game::is_tile_enemy_start(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy_start*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

bool Game::is_tile_enemy_end(sf::Vector2i index)
{
    return  ( !(dynamic_cast<Tile_enemy_end*>
                (Tile::get_tile_by_index(index)) == nullptr) );
}

void Game::render()
{
    window.clear();
    // render tiles
    for (auto it{begin(Tile::tiles)}; it != end(Tile::tiles); ++it)
    {
        window.draw(*it->second);
    }
    window.display();
}
//
// void Game::load_entities(string const & file)
// {
//     ifstream ifs(file);
//     if (ifs.is_open())
//     {
//         json j_data;
//         ifs >> j_data;
//         init_enemies(j_data["Enemies"]);
//         init_projectiles(j_data["Projectiles"]);
//         init_towers(j_data["Towers"]);
//     }
//     ifs.close();
// }
//
// void Game::init_enemies(json const & json_obj)
// {
//     json enemy = json_obj["Enemy_basic"];
//     Enemy_basic::life_init = enemy["life_init"];
//
//     enemy = json_obj["Enemy_boss"];
//     Enemy_boss::life_init = enemy["life_init"];
//
// }
//
// void Game::init_projectiles(json const & json_obj)
// {
//     json proj = json_obj["Projectile_basic"];
//     Projectile_basic::frames_to_live = proj["frames_to_live"];
//     Projectile_basic::damage_init = proj["damage_init"];
//
//     proj = json_obj["Projectile_pierce"];
//     Projectile_basic::frames_to_live = proj["frames_to_live"];
//     Projectile_basic::damage_init = proj["damage_init"];
//
//     proj = json_obj["Projectile_bomb"];
//     Projectile_basic::frames_to_live = proj["frames_to_live"];
//     Projectile_basic::damage_init = proj["damage_init"];
//
//     proj = json_obj["Projectile_bomb_blast"];
//     Projectile_basic::frames_to_live = proj["frames_to_live"];
//     Projectile_basic::damage_init = proj["damage_init"];
// }
//
// void Game::init_towers(json const & json_obj)
// {
//     json tower = json_obj["Tower_basic"];
//     Tower_basic::detection_radius_init = tower["detection_radius_init"];
//     Tower_basic::sprite_init.setTexture(resources.load(tower["sprite_init"]));
//     Tower_basic::fire_period_init = tower["fire_period_init"];
//     Tower_basic::projectile_init = get_tower_projectile(tower["projectile_init"]);
//     Tower_basic::shop_sprite_init.setTexture(resources.load(tower["shop_sprite_init"]));
//     Tower_basic::cost_init = tower["cost_init"];
//
//     tower = json_obj["Tower_ring"];
//     Tower_ring::detection_radius_init = tower["detection_radius_init"];
//     Tower_ring::sprite_init.setTexture(resources.load(tower["sprite_init"]));
//     Tower_ring::fire_period_init = tower["fire_period_init"];
//     Tower_ring::projectile_init = get_tower_projectile(tower["projectile_init"]);
//     Tower_ring::shop_sprite_init.setTexture(resources.load(tower["shop_sprite_init"]));
//     Tower_ring::cost_init = tower["cost_init"];
// }
//
// void Game::check_collision()
// {
//     //kolla tower - enemy
//     vector<Enemy*> *enemies = &Enemy::enemies;
//     vector<Projectile*> *projectiles = &Projectile::projectiles;
//     vector<Tower*> *towers = &Tower::static_towers;
//     for (auto enemy_it = Enemy::enemies.begin();
//          enemy_it != Enemy::enemies.end();
//          enemy_it++)
//     {
//         // kolla kollision mellan projectile - enemy
//         for (auto projectile_it = Projectile::projectiles.begin();
//          projectile_it != Projectile::projectiles.end();
//          projectile_it++)
//         {
//             if (collided((*projectile_it),(*enemy_it)))
//             {
//                 (*enemy_it)->collision(*projectile_it);
//                 (*projectile_it)->collision();
//             }
//         }
//         for (auto tower_it = Tower::static_towers.begin();
//              tower_it != Tower::static_towers.end();
//              tower_it++)
//         {
//             if (collided((*tower_it),(*enemy_it)))
//             {
//                 (*tower_it)->collision((*enemy_it));
//             }
//         }
//     }
// }
// void fire_towers()
// {
//     for (auto tower = Tower::static_towers.begin();
//          tower != Tower::static_towers.end();
//          tower++)
//         {
//             (*tower)->shoot();
//         }
// }
//
// void Game::handle_events()
// {
//  while (window.pollEvent(event))
//     {
//         if ( event.type == Event::Closed )
//         {
//             window.close ();
//         }
//         // Has a mouse button been pressed?
//         else if ( event.type == Event::MouseButtonPressed )
//         {
//             auto mouse { event.mouseButton };
//             // Is it the left mouse button?
//             if ( mouse.button == Mouse::Button::Left )
//             {
//                 handle_click(sf::Vector2f(mouse.x, mouse.y));
//             }
//         }
//     }
// }
//
// void Game::handle_click(sf::Vector2f click)
// {
//     // Do we want to be smart or dumb here? One way is to just itterate over all
//     // clickable object and see if they contain the clicked location. A faster
//     // way is to use the fact that everything is in a grid and calculate what
//     // button was pressed. I did the dump way.
//
//     // Itterate over tower_butons
//     for (auto b = Tower_button.buttons.begin(); b != Tower_button.buttons.end(); b++)
//     {
//         if(clickable->getGlobalBounds().contains(musposition))
//         {
//             (*b)->on_click();
//         }
//     }
//
//     // Itterate over tiles
//     for (auto t = Tile.tiles.begin();t != Tile.tiles.end(); t++)
//     {
//         if(clickable->getGlobalBounds().contains(musposition))
//         {
//             (*t)->on_click();
//         }
//     }
// }
