#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <math.h>
#include <sstream>
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
#include "Tower_shop.h"

using namespace std;
using json = nlohmann::json;
float Tile::side_length = 50; // flytta
int Game::frame =0;



// Help function to determine init projectile for tower
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
    infile.close();
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
        if ( is_tile_enemy_end((*it).first) )
            enemy_end = (*it).second->get_index_position();
    }
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
        direction.x = last_tile.x - current_tile.x;
        direction.y = last_tile.y - current_tile.y;
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

    for (auto it{begin(Tower::static_towers)}; it != end(Tower::static_towers); ++it)
    {
        window.draw(*(*it)); // it doesn't make sense to me either but it works
    }

    //render projectiles
    for (auto it = begin(Projectile::projectiles);
         it != end(Projectile::projectiles);
         ++it)
    {
        window.draw(*(*it));
    }

    shop.render(window);
    // render health
    health.render();

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
        Tile* tile = Tile::get_tile_by_coord((*it)->getPosition());
        if ( tile->update_enemy(*it) > 0 )
        {
            damage_dealt += tile->update_enemy(*it);
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

void Game::projectile_update_position()
{
    for (auto it{begin(Projectile::projectiles)}; it != end(Projectile::projectiles);)
    {
      if(!(*it)->update_position())
      {
        delete *it;
        it = Projectile::projectiles.erase(it);
      }
      else
      {
        ++it;
      }
    }
}
void Game::load_entities(string const & file)
{
    ifstream ifs(file);
    if (ifs.is_open())
    {
        json j_data;
        ifs >> j_data;
        init_enemies(j_data["Enemy"]);
        init_towers(j_data["Tower"]);
        init_projectiles(j_data["Projectile"]);
        init_shop(j_data["Shop"]);
    }
    ifs.close();
}

 void Game::init_enemies(json const & json_obj)
{
    json enemy_basic = json_obj["Enemy_basic"];
    Enemy_basic::life_init = enemy_basic["life_init"];
    Enemy_basic::position_init = sf::Vector2f{40, 120};
    Enemy_basic::prop.texture_file = enemy_basic["texture"];
    sf::Vector2f size_basic;
    size_basic.x = enemy_basic["size"][0];
    size_basic.y = enemy_basic["size"][1];
    Enemy_basic::prop.size = sf::Vector2f{size_basic};
    Enemy_basic::prop.hit_rad = enemy_basic["hit_rad"];
    Enemy_basic::prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Enemy_basic::prop.mov_spd = enemy_basic["mov_spd"];

    json enemy_boss = json_obj["Enemy_boss"];
    Enemy_boss::life_init = enemy_boss["life_init"];
    //Enemy_boss::position_init = sf::Vector2f{500, 500}; // ERROR, this one seems to write over Enemy_basic::position_init
    Enemy_boss::prop.texture_file = enemy_boss["texture"];
    sf::Vector2f size_boss;
    size_boss.x = enemy_boss["size"][0];
    size_boss.y = enemy_boss["size"][1];
    Enemy_boss::prop.size = sf::Vector2f{size_boss};
    Enemy_boss::prop.hit_rad = enemy_boss["hit_rad"];
    Enemy_boss::prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Enemy_boss::prop.mov_spd = enemy_boss["mov_spd"];

    cout << "laddat enemies" << endl;
}

void Game::create_1_enemy_basic()
{
    Enemy::new_basic();
}

void Game::create_1_enemy_boss()
{
    Enemy::new_boss();
}

void Game::create_n_enemy_basic(int start_time, int amount, float interval)
{
    if ( (frame >= (start_time * fps))                              &&
         (frame <  (start_time * fps) + (fps * interval * amount )) &&
         (fmod(frame ,(fps * interval)) == 0)                         )
    {
        create_1_enemy_basic();
    }
}

void Game::create_n_enemy_boss(int start_time, int amount, float interval)
{
    if ( (frame >= (start_time * fps))                              &&
         (frame <  (start_time * fps) + (fps * interval * amount )) &&
         (fmod(frame ,(fps * interval)) == 0)                         )
    {
        create_1_enemy_boss();
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

void Game::init_projectiles(json const & json_obj)
{   cout << "ladda in projectile basic" << endl;
    json proj = json_obj["Projectile_basic"];
    Projectile_basic::frames_to_live = proj["frames_to_live"];
    Projectile_basic::damage_init = proj["damage_init"];
    Projectile_basic::prop.texture_file = proj["texture"];
    Projectile_basic::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_basic::prop.hit_rad = proj["hit_rad"];
    Projectile_basic::prop.dir = sf::Vector2f(0,0);
    Projectile_basic::prop.mov_spd = proj["mov_spd"];

    proj = json_obj["Projectile_pierce"];
    Projectile_pierce::frames_to_live = proj["frames_to_live"];
    Projectile_pierce::damage_init = proj["damage_init"];
    Projectile_pierce::prop.texture_file = proj["texture"];
    Projectile_pierce::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_pierce::prop.hit_rad = proj["hit_rad"];
    Projectile_pierce::prop.dir = sf::Vector2f(0,0);
    Projectile_pierce::prop.mov_spd = proj["mov_spd"];

    proj = json_obj["Projectile_bomb"];
    Projectile_bomb::frames_to_live = proj["frames_to_live"];
    Projectile_bomb::damage_init = proj["damage_init"];
    Projectile_bomb::prop.texture_file = proj["texture"];
    Projectile_bomb::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_bomb::prop.hit_rad = proj["hit_rad"];
    Projectile_bomb::prop.dir = sf::Vector2f(0,0);
    Projectile_bomb::prop.mov_spd = proj["mov_spd"];

    proj = json_obj["Projectile_bomb_blast"];
    Projectile_bomb_blast::frames_to_live = proj["frames_to_live"];
    Projectile_bomb_blast::damage_init = proj["damage_init"];
    Projectile_bomb_blast::prop.texture_file = proj["texture"];
    Projectile_bomb_blast::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_bomb_blast::prop.hit_rad = proj["hit_rad"];
    Projectile_bomb_blast::prop.dir = sf::Vector2f(0,0);
    Projectile_bomb_blast::prop.mov_spd = proj["mov_spd"];
}

void Game::init_towers(json const & json_obj)
{
    cout << "börjar ladda towers" << endl;
    json tower = json_obj["Tower_basic"];

    Tower_basic::tower_prop.projectile_init = get_tower_projectile(tower["projectile_init"]);
    Tower_basic::tower_prop.cost_init = tower["cost_init"];
    Tower_basic::tower_prop.fire_period_init = tower["fire_period_init"];
    Tower_basic::entity_prop.texture_file = tower["sprite_init"];
    Tower_basic::entity_prop.size = sf::Vector2f{tower["size"][0], tower["size"][1]};
    Tower_basic::entity_prop.hit_rad = tower["detection_radius_init"];
    Tower_basic::entity_prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Tower_basic::entity_prop.mov_spd = 0;

    tower = json_obj["Tower_ring"];
    //Tower_ring::tower_prop.projectile_init = get_tower_projectile(tower["projectile_init"]);
    Tower_ring::tower_prop.cost_init = tower["cost_init"];
    Tower_ring::tower_prop.fire_period_init = tower["fire_period_init"];
    Tower_ring::entity_prop.texture_file = tower["sprite_init"];
    Tower_ring::entity_prop.size = sf::Vector2f{tower["size"][0], tower["size"][1]};
    Tower_ring::entity_prop.hit_rad = tower["detection_radius_init"];
    Tower_ring::entity_prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Tower_ring::entity_prop.mov_spd = 0;

    cout << "laddat towers" << endl;
}

void Game::init_shop(json const & j_shop)
{
    Wallet wallet{j_shop["start_cash"]};
    sf::Vector2f shop_size{j_shop["shop_size"][0], j_shop["shop_size"][1]};
    sf::Vector2f btn_size{j_shop["btn_size"][0], j_shop["btn_size"][1]};
    sf::Vector2f shop_pos{window.getSize().x - shop_size.x, 0};
    json back_color = j_shop["background_color"];
    sf::Color color{back_color["r"], back_color["g"], back_color["b"]};
    json btn_color = j_shop["btn_color"];
    sf::Color button_color{btn_color["r"], btn_color["g"], btn_color["b"]};
    json btn_select_color = j_shop["btn_select_color"];
    sf::Color button_select_color{btn_select_color["r"], btn_select_color["g"], btn_select_color["b"]};
    vector<Tower *> passive_towers{new Tower_basic{}, new Tower_basic, new Tower_basic, new Tower_basic, new Tower_basic}; //TODO! change to other
    shop = Tower_shop{passive_towers, wallet, shop_pos, shop_size,btn_size, color,button_color,button_select_color};
}


void Game::check_collision()
{
    //kolla tower - enemy
    for (auto enemy_it = Enemy::enemies.begin();
         enemy_it != Enemy::enemies.end(); enemy_it++)
    {
        // kolla kollision mellan projectile - enemy
        for (auto projectile_it = Projectile::projectiles.begin();
         projectile_it != Projectile::projectiles.end();)
        {
            if (collided((*projectile_it),(*enemy_it)))
            {
                if ((*enemy_it)->collision(*projectile_it))
                {
                  delete *enemy_it;
                  enemy_it = Enemy::enemies.erase(enemy_it);
                }
                if ((*projectile_it)->collision())
                {
                  delete *projectile_it;
                  projectile_it = Projectile::projectiles.erase(projectile_it);
                }
                else
                {
                  ++projectile_it;
                }
            }
            else
            {
                ++projectile_it;
            }

        }
        for (auto tower_it = Tower::static_towers.begin();
             tower_it != Tower::static_towers.end();
             tower_it++)
        {
            if (collided((*tower_it),(*enemy_it)))
            {
                (*tower_it)->collision((*enemy_it));
            }
        }
    }
}

void Game::fire_towers()
{
    for (auto tower = Tower::static_towers.begin();
         tower != Tower::static_towers.end();
         tower++)
        {
            (*tower)->shoot();
        }
}

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
             else if ( event.type == sf::Event::MouseButtonPressed )
             {
                 auto mouse { event.mouseButton };
                 // Is it the left mouse button?
                 if ( mouse.button == sf::Mouse::Button::Left )
                 {
                     float mouseX = mouse.x;
                     float mouseY = mouse.y;
                     handle_click(sf::Vector2f{mouseX, mouseY});
                 }
             }
        }
}

 void Game::handle_click(sf::Vector2f click)
 {
     // Do we want to be smart or dumb here? One way is to just itterate over all
     // clickable object and see if they contain the clicked location. A faster
     // way is to use the fact that everything is in a grid and calculate what
     // button was pressed. I did the dump way.

             shop.on_click(click);

     // Itterate over tiles
     /*
     for (auto t = Tile::tiles.begin();t != Tile::tiles.end(); t++)
     {
         if(t->getGlobalBounds().contains(click))
         {
             (*t)->on_click();
         }
     }
     */
 }

void Game::update_logic()
{
    if ( Enemy::enemies.size() > 0 )
    {
        enemy_update_direction();
        enemy_update_position();
    }
    if (Projectile::projectiles.size() > 0)
    {
        projectile_update_position();
    }
    check_collision();
    frame++;
}
