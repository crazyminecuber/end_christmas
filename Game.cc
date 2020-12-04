#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <math.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp" // to parse data from json file. See json.hpp for source.

#include "Game.h"
#include "Enemy.h"
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
#include "Wave_manager.h"

using namespace std;
using json = nlohmann::json;
float Tile::side_length = 50; // flytta

// Help function to determine init projectile for tower
/*
Projectile* Game::get_tower_projectile(std::string const & projectile)
{
    sf::Vector2f double0{0,0};//7
    if(projectile == "Projectile_basic")
    {
        return new Projectile_basic{double0,double0};
    }
    else if(projectile == "Projectile_pierce")
    {
        return new Projectile_pierce{double0,double0};
    }
    else if(projectile == "Projectile_bomb")
    {
        return new Projectile_bomb{double0,double0};
    }
    else
    {
        __throw_bad_function_call();
    }
}

// Help function to determine if object1 and object2 have collided
bool Game::collided(Entity const *object1, Entity const *object2)
{
    return (pow(object1->getPosition().x - object2->getPosition().x,2)
            < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
            && pow(object1->getPosition().y - object2->getPosition().y,2)
            < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
           );
}
*/
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
                Tile::tiles[tile_index_pos] = new Tile_nothing("resources/textures/stones.jpg", window, tile_index_pos);
            }
            else if ( num == 1 )
            {
                Tile::tiles[tile_index_pos] = new Tile_tower("resources/textures/grass.jpg", window, tile_index_pos);
            }
            else if ( num == 2 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy("resources/textures/dirt.jpg", window, tile_index_pos);
            }
            else if ( num == 3 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy_start("resources/textures/dirt.jpg", window, tile_index_pos);
            }
            else if ( num == 4 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy_end("resources/textures/dirt.jpg", window, tile_index_pos);
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
    Tile::side_length = std::min(window_size.x/tiles_per_row,
                                 window_size.y/tiles_per_col);
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
    sf::Vector2f direction;

    /* find enemy_end tile */
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
    {
        if ( Tile::is_tile_enemy_end((*it).first) )
            enemy_end = (*it).second->get_index_position();
    }
    current_tile = enemy_end;

    /* loop through enemy path backwards and set set direction of tile */
    while ( !(Tile::is_tile_enemy_start(current_tile)) )
    {
        /* if (tile exists) and (tile is enemy) and (tile is not last tile) */
        // look up
        if ( Tile::tiles.find(current_tile + sf::Vector2i{0, -1})  !=
                Tile::tiles.end()                                  &&
             Tile::is_tile_enemy(  (current_tile + sf::Vector2i{0, -1})) &&
             last_tile !=    (current_tile + sf::Vector2i{0, -1})     )
        {
            next_tile = current_tile + sf::Vector2i{0, -1};
        }
        // look right
        if ( Tile::tiles.find(current_tile + sf::Vector2i{1, 0})  !=
                Tile::tiles.end()                                 &&
             Tile::is_tile_enemy(  (current_tile + sf::Vector2i{1, 0})) &&
             last_tile !=    (current_tile + sf::Vector2i{1, 0})     )
        {
            next_tile = current_tile + sf::Vector2i{1, 0};
        }
        // look down
        if ( Tile::tiles.find(current_tile + sf::Vector2i{0, 1})  !=
                Tile::tiles.end()                                 &&
             Tile::is_tile_enemy(  (current_tile + sf::Vector2i{0, 1})) &&
             last_tile !=    (current_tile + sf::Vector2i{0, 1})     )
        {
            next_tile = current_tile + sf::Vector2i{0, 1};
        }
        // look left
        if ( Tile::tiles.find(current_tile + sf::Vector2i{-1, 0})  !=
                Tile::tiles.end()                                  &&
             Tile::is_tile_enemy(  (current_tile + sf::Vector2i{-1, 0})) &&
             last_tile !=    (current_tile + sf::Vector2i{-1, 0})     )
        {
            next_tile = current_tile + sf::Vector2i{-1, 0};
        }

        // prepare for next iteration
        last_tile = current_tile;
        current_tile = next_tile;

        // set direction
        direction.x = last_tile.x - current_tile.x;
        direction.y = last_tile.y - current_tile.y;
        Tile::get_tile_by_index(current_tile)->set_direction(direction);
    }
}

void Game::render()
{
    window.clear();

    /* Put stuff to render here */
    // OBS: ORDER MATTERS!

    // render tiles
    for (auto it{begin(Tile::tiles)}; it != end(Tile::tiles); ++it)
    {
        window.draw(*it->second);
    }

    // render enemies
    for (auto it{begin(Enemy::enemies)}; it != end(Enemy::enemies); ++it)
    {
        window.draw(*(*it)); // it doesn't make sense to me either but it works
    }

    // render health
    health.render();
    wave_manager.render();

    /*  ---------------------- */

    window.display();
}

bool Game::is_running()
{
    return window.isOpen();
}

void Game::enemy_update_direction()
{
    float damage_dealt{0};
    for (auto it{Enemy::enemies.begin()}; it != Enemy::enemies.end();)
    {
        float damage_this_enemy{0};
        Tile* tile = Tile::get_tile_by_coord((*it)->getPosition());
        // maybe change this later so that the deletion is done inside
        // tile_enemy_end instead. Have to change flow of information
        // between damage and health then too.
        damage_this_enemy = tile->update_enemy(*it);
        if ( damage_this_enemy > 0.f )
        {
            damage_dealt += damage_this_enemy;
            delete *it;
            it = Enemy::enemies.erase(it);
        }
        else
            ++it;
    }
    health.remove_n_health(damage_dealt);
}

void Game::enemy_update_position()
{
    for (auto it{begin(Enemy::enemies)}; it != end(Enemy::enemies); ++it)
    {
        (*it)->move((*it)->direction * (*it)->movement_speed);
    }
}

void Game::next_wave()
{
    // wave_manager.next_wave(fps);
}

void Game::load_entities(string const & file)
{
    ifstream ifs(file);
    if (ifs.is_open())
    {
        json j_data;
        ifs >> j_data;
        init_enemies(j_data["Enemy"]);
        init_waves(j_data["Waves"]);
        // init_projectiles(j_data["Projectiles"]);
        // init_towers(j_data["Towers"]);
    }
    ifs.close();
}

 void Game::init_enemies(json const & json_obj)
{
    /* position_init */
    sf::Vector2f tile_enemy_start_position;
    tile_enemy_start_position = Tile::get_tile_enemy_start()->getPosition() +
                                sf::Vector2f{(Tile::side_length / 2.f),
                                             (Tile::side_length / 2.f) };
    Enemy::position_init = tile_enemy_start_position;

    /* Enemy_basic */
    json enemy_basic = json_obj["Enemy_basic"];
    Enemy_basic::life_init = enemy_basic["life_init"];
    Enemy_basic::prop.texture_file = enemy_basic["texture"];
    sf::Vector2f size_basic;
    size_basic.x = enemy_basic["size"][0];
    size_basic.y = enemy_basic["size"][1];
    Enemy_basic::prop.size = sf::Vector2f{size_basic};
    Enemy_basic::prop.hit_rad = enemy_basic["hit_rad"];
    Enemy_basic::prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Enemy_basic::prop.mov_spd = enemy_basic["mov_spd"];

    /* Enemy_boss */
    json enemy_boss = json_obj["Enemy_boss"];
    Enemy_boss::life_init = enemy_boss["life_init"];
    Enemy_boss::prop.texture_file = enemy_boss["texture"];
    sf::Vector2f size_boss;
    size_boss.x = enemy_boss["size"][0];
    size_boss.y = enemy_boss["size"][1];
    Enemy_boss::prop.size = sf::Vector2f{size_boss};
    Enemy_boss::prop.hit_rad = enemy_boss["hit_rad"];
    Enemy_boss::prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Enemy_boss::prop.mov_spd = enemy_boss["mov_spd"];
}

void Game::init_waves(json const & json_obj)
{
    //Get every wave and add to wave_groups
    for (const auto& wave : json_obj.items())
    {
        Enemy* enemy;
        if(wave.value()["enemy"] == "Enemy_basic")
        {
            enemy = Enemy::get_new_enemy_basic();
        }
        else if(wave.value()["enemy"] == "Enemy_boss")
        {
            enemy = Enemy::get_new_enemy_boss();
        }
    wave_manager.add_wave(new Wave_group(
                          wave.value()["start_wave"],
                          wave.value()["end_wave"],
                          enemy,
                          wave.value()["spawn_delay"],
                          wave.value()["spawn_rate"],
                          wave.value()["num_in_group"],
                          wave.value()["num_in_group_inc"],
                          wave.value()["group_spawn_interval"],
                          wave.value()["num_of_groups"],
                          wave.value()["num_of_groups_inc"],
                          wave.value()["mov_spd_factor"]));
    cout << wave.key() << endl;
    }
}

int Game::get_frame()
{
    return frame;
}

float Game::get_fps()
{
    return fps;
}

//
// void Game::init_projectiles(json const & json_obj)
// {
//     json proj = json_obj["Projectile_basic"];
//     Projectile_basic::frames_to_live = proj["frames_to_live"];
//     Projectile_basic::damage_init = proj["damage_init"];
//std::cout << "Text begin" << std::endl;
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
void Game::handle_input()
{
    sf::Event event;
    while (window.pollEvent(event))
        {
            if ( event.type == sf::Event::Closed )
            {
                window.close ();
            }
            // Has a mouse button been pressed?
            // else if ( event.type == sf::Event::MouseButtonPressed )
            // {
            //     auto mouse { event.mouseButton };
            //     // Is it the left mouse button?
            //     if ( mouse.button == sf::Mouse::Button::Left )
            //     {
            //         float mouseX = mouse.x;
            //         float mouseY = mouse.y;
            //         handle_click(sf::Vector2f{mouseX, mouseY});
            //     }
            // }
        }
}

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

void Game::update_logic()
{
    if(Enemy::enemies.size() == 0 && wave_manager.all_enemies_have_spawned())
    {
        cout << "next_wave" << endl;
        wave_manager.next_wave(frame, fps);
    }
    wave_manager.spawn_enemies(frame);
    enemy_update_direction();
    enemy_update_position();
    frame++;
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

/* overload stream operator för sf::Vector2u */
std::ostream& operator<<(std::ostream& output, sf::Vector2u const & vector)
{
    output << "(" << vector.x << ", " << vector.y << ")";
    return output;
}
