#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <math.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp" // to parse data from json file. See json.hpp for source.

#include "State_machine.h"
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
#include "Wave_manager.h"

using namespace std;
using json = nlohmann::json;
int Game::frame =0;

Game::~Game()
{
    for (Projectile *p : Projectile::projectiles)
    {
        delete p;
    }
    Projectile::projectiles.clear();

    for (Enemy *e : Enemy::enemies)
    {
        delete e;
    }
    Enemy::enemies.clear();


    for (Tower *t : Tower::towers)
    {
        delete t;
    }
    Tower::towers.clear();

    for (auto it = Tile::tiles.begin(); it != Tile::tiles.end(); it++)
    {
        delete (*it).second;
    }
    Tile::tiles.clear();
}

// Help function to determine init projectile for tower
Projectile* Game::get_tower_projectile(std::string const & projectile)
{

    sf::Vector2f double0{0,0};
    if(projectile == "Projectile_basic")
    {
       return new Projectile_basic(double0,double0);
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
/* Help function to determine if object1 and object2 have collided.
 * "returns" the squared distance in sq_distance.
 */
bool Game::collided(Entity const *object1, Entity const *object2, float & sq_distance)
{
    sf::Vector2f distance{0,0};
    distance.x = pow(object1->getPosition().x - object2->getPosition().x,2);
    distance.y = pow(object1->getPosition().y - object2->getPosition().y,2);
    sq_distance = distance.x + distance.y;
    return ( distance.x
            < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
            && distance.y
            < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
           );
}

bool Game::collided_bb(Entity const *object1, Entity const *object2)
{
    return (object1->getGlobalBounds().intersects(object2->getGlobalBounds()));
}

void Game::load_map(string const & file_entity)
{
    /* prepare variables needed for reading from file */
    std::ifstream infile{maps[selected_map]["file_name"]};
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
                Tile::tiles[tile_index_pos] = new Tile_nothing(
                    map_tiles[selected_map]["0"], tile_index_pos);
            }
            else if ( num == 1 )
            {
                Tile::tiles[tile_index_pos] = new Tile_tower(
                    map_tiles[selected_map]["1"], tile_index_pos);
            }
            else if ( num == 2 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy(
                    map_tiles[selected_map]["2"], tile_index_pos);
            }
            else if ( num == 3 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy_start(
                    map_tiles[selected_map]["3"], tile_index_pos);
            }
            else if ( num == 4 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy_end(
                    map_tiles[selected_map]["4"], tile_index_pos);
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

    /* update side_length */
    // calculate Tile::side_length and change all tiles
    float shop_sizeX = read_shop_width(file_entity);

    int tiles_per_col = tile_index_pos.x + (1 - 2);
    int tiles_per_row = tile_index_pos.y + (1 - 2);
    float max_size_win_x = (window->getSize().x - shop_sizeX)/tiles_per_col;
    float max_size_win_y = window->getSize().y/tiles_per_row;
    float max_size_screen_x = (sf::VideoMode::getDesktopMode().width
                                - shop_sizeX)/tiles_per_col;
    float max_size_screen_y = sf::VideoMode::getDesktopMode().height
                                             /tiles_per_row;
    Tile::side_length = std::min({max_size_win_x, max_size_win_y,
                                  max_size_screen_x, max_size_screen_y});
    for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
    {
        (*it).second->update_side_length();
    }

    /* update window size */
    unsigned new_window_sizeX = tiles_per_col*Tile::side_length + shop_sizeX;
    unsigned new_window_sizeY = tiles_per_row*Tile::side_length;
    window->create(sf::VideoMode{new_window_sizeX, new_window_sizeY}, "Kill santa", sf::Style::Close);

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
    int tile_number{0};

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

        // set tile_number
        Tile::get_tile_by_index(current_tile)->set_tile_number(tile_number);
        tile_number++;

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
    /* Put stuff to render here */
    // OBS: ORDER MATTERS!

    // render tiles
    for (auto it{begin(Tile::tiles)}; it != end(Tile::tiles); ++it)
    {
        window->draw(*it->second);
    }

    // render enemies
    for (auto it{begin(Enemy::enemies)}; it != end(Enemy::enemies); ++it)
    {
        window->draw(*(*it)); // it doesn't make sense to me either but it works
    }

    // render towers
    for (auto it{begin(Tower::towers)}; it != end(Tower::towers); ++it)
    {
        window->draw(*(*it)); // it doesn't make sense to me either but it works
    }

    // render tower radii
    if ( render_tower_radii )
    {
        for (auto it{begin(Tower::towers)}; it != end(Tower::towers); ++it)
        {
            window->draw((*(*it)).circle_hit_rad);
        }
    }

    //render projectiles
    for (auto it = begin(Projectile::projectiles);
         it != end(Projectile::projectiles);
         ++it)
    {
        window->draw(*(*it));
    }

    // render shop
    shop.render(*window);

    // render health
    health.render();

    // render wave_manager
    wave_manager.render();
}


void Game::enemy_update_direction()
{
    float damage_dealt{0};
    for (size_t i = 0; i < Enemy::enemies.size(); i++)
    {
        // cout << "iterator at end " << (it != Enemy::enemies.end()) << endl;
        float damage_this_enemy{0};
        Tile* tile = Tile::get_tile_by_coord(Enemy::enemies[i]->getPosition());
        // maybe change this later so that the deletion is done inside
        // tile_enemy_end instead. Have to change flow of information
        // between damage and health then too.
        damage_this_enemy = tile->update_enemy(Enemy::enemies[i]);
        if ( damage_this_enemy > 0.f )
        {
            damage_dealt += damage_this_enemy;
            delete Enemy::enemies[i];
            if(Enemy::enemies.size()>0)
            {
                swap(Enemy::enemies.at(i),Enemy::enemies.back());
            }

            Enemy::enemies.pop_back();
            //Enemy::enemies.erase(Enemy::enemies.begin() + i);
        }
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

bool Game::wave_complete()
{
    return wave_manager.wave_is_finished();
}

bool Game::player_has_won()
{
    return wave_manager.player_has_won();
}

void Game::projectile_update_position()
{
    for (auto it = Projectile::projectiles.begin(); it != Projectile::projectiles.end();)
    {
      if(!((*it)->update_position(window->getSize())))
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

void Game::next_wave()
{
    wave_manager.next_wave(frame);
}

int Game::get_current_wave() const
{
    return wave_manager.get_current_wave();
}

float Game::read_shop_width(string const & file_entity)
/* window needs shop_width and shop needs window size.
   This function gets around the circular dependency */
{
    float shop_sizeX;

    ifstream ifs(file_entity);
    if (ifs.is_open())
    {
        json j_data;
        ifs >> j_data;
        shop_sizeX = j_data["Shop"]["shop_size"][0];
        ifs.close();
    }
    else
    {
        throw invalid_argument("Could not open " + file_entity);
    }

    return shop_sizeX;
}

void Game::load_entities(string const & file_entity)
{
    ifstream ifs(file_entity);
    if (ifs.is_open())
    {
        json j_data;
        ifs >> j_data;
        init_projectiles(j_data["Projectile"]);
        init_towers(j_data["Tower"]);
        init_shop(j_data["Shop"]);
        init_waves(j_data["Waves"], j_data["Enemy"]);
        ifs.close();
    }
    else
    {
        throw invalid_argument("Could not open " + file_entity);
    }
}

void Game::init_tiles(string const & file_entity)
{
    // read from file and save data in maps and map_tiles
    ifstream ifs(file_entity);
    json json_obj;
    if (ifs.is_open())
    {
        json j_data;
        ifs >> j_data;
        json_obj = j_data["Maps"];
    }
    ifs.close();

    string map_name;
    map<string, string> inner_map;

    /* populate maps */
    string file_name;
    string display_name;
    string difficulty;
    for (const auto& map : json_obj.items())
    {
        map_name = map.key();
        file_name = map.value()["file_name"];
        display_name = map.value()["display_name"];
        difficulty = map.value()["difficulty"];

        inner_map.clear();
        inner_map.insert({"file_name", file_name});
        inner_map.insert({"display_name", display_name});
        inner_map.insert({"difficulty", difficulty});
        maps.insert({map_name, inner_map});
    }
    // cout << maps["map_dev"]["file_name"] << endl;

    /* populate map_tiles */
    string zero;
    string one;
    string two;
    string three;
    string four;
    for (const auto& map : json_obj.items())
    {
        map_name = map.key();
        zero = map.value()["tiles"]["0"];
        one = map.value()["tiles"]["1"];
        two = map.value()["tiles"]["2"];
        three = map.value()["tiles"]["3"];
        four = map.value()["tiles"]["4"];

        inner_map.clear();
        inner_map.insert({"0", zero});
        inner_map.insert({"1", one});
        inner_map.insert({"2", two});
        inner_map.insert({"3", three});
        inner_map.insert({"4", four});
        map_tiles.insert({map_name, inner_map});
    }
    // cout << map_tiles["map_dev"]["0"] << endl;
}

void Game::init_waves(json const & waves, json const & enemies)
{
    sf::Vector2f position_init = Tile::get_tile_enemy_start()->getPosition() +
                                sf::Vector2f{(Tile::side_length / 2.f),
                                             (Tile::side_length / 2.f) };
    //Get every wave and add to wave_groups
    for (const auto& wave : waves.items())
    {
    //Passive enemy for the wave_group
    Enemy* enemy = Enemy::get_new_enemy(enemies, wave.value()["enemy"], position_init);

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
                          wave.value()["num_of_groups_inc"]));
    }
    wave_manager.init_waves(frame);
}

void Game::init_projectiles(json const & json_obj)
{
    json proj = json_obj["Projectile_basic"];
    Projectile_basic::frames_to_live = proj["frames_to_live"];
    Projectile_basic::damage_init = proj["damage_init"];
    Projectile_basic::prop.texture_file = proj["texture"];
    Projectile_basic::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_basic::prop.hit_rad = proj["hit_rad"];
    Projectile_basic::prop.dir = sf::Vector2f(0,0);
    Projectile_basic::prop.mov_spd = proj["mov_spd"];
    Projectile_basic::rotation_offset_init = proj["rotation_offset"];

    proj = json_obj["Projectile_pierce"];
    Projectile_pierce::frames_to_live = proj["frames_to_live"];
    Projectile_pierce::damage_init = proj["damage_init"];
    Projectile_pierce::prop.texture_file = proj["texture"];
    Projectile_pierce::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_pierce::prop.hit_rad = proj["hit_rad"];
    Projectile_pierce::prop.dir = sf::Vector2f(0,0);
    Projectile_pierce::prop.mov_spd = proj["mov_spd"];
    Projectile_pierce::nr_pierce_init = proj["nr_pierce_init"];
    Projectile_pierce::rotation_offset_init = proj["rotation_offset"];

    proj = json_obj["Projectile_bomb"];
    Projectile_bomb::frames_to_live = proj["frames_to_live"];
    Projectile_bomb::damage_init = proj["damage_init"];
    Projectile_bomb::prop.texture_file = proj["texture"];
    Projectile_bomb::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_bomb::prop.hit_rad = proj["hit_rad"];
    Projectile_bomb::prop.dir = sf::Vector2f(0,0);
    Projectile_bomb::prop.mov_spd = proj["mov_spd"];
    Projectile_bomb::rotation_offset_init = proj["rotation_offset"];

    proj = json_obj["Projectile_bomb_blast"];
    Projectile_bomb_blast::frames_to_live = proj["frames_to_live"];
    Projectile_bomb_blast::damage_init = proj["damage_init"];
    Projectile_bomb_blast::prop.texture_file = proj["texture"];
    Projectile_bomb_blast::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_bomb_blast::prop.hit_rad = proj["hit_rad"];
    Projectile_bomb_blast::prop.dir = sf::Vector2f(0,0);
    Projectile_bomb_blast::prop.mov_spd = proj["mov_spd"];
    Projectile_bomb_blast::rotation_offset_init = proj["rotation_offset"];
}

void Game::init_towers(json const & json_obj)
{
    // Itterativly make tower_basics factories from file
    json tower = json_obj["Tower_basics"];
    for (auto& tow : tower)
    {
        Tower::factory_towers.push_back(new Tower_basic{
            tow["sprite_init"],
            sf::Vector2f{tow["size"][0], tow["size"][1]},
            tow["detection_radius_init"],
            tow["cost_init"],
            get_tower_projectile(tow["projectile_init"]),
            tow["fire_period_init"]
    });

    }
    tower = json_obj["Tower_rings"];

    // Itterativly make tower_rings factories from file
    for (auto& tow : tower)
    {
        Tower::factory_towers.push_back(new Tower_ring{
            tow["sprite_init"],
            sf::Vector2f{tow["size"][0], tow["size"][1]},
            tow["detection_radius_init"],
            tow["cost_init"],
            get_tower_projectile(tow["projectile_init"]),
            tow["fire_period_init"],
            tow["num_projectile_init"]
        });
    }
}

void Game::init_shop(json const & j_shop)
{
    float window_sizeY = window->getSize().y;
    wallet = Wallet{j_shop["start_cash"]};
    string font_name{j_shop["font_name"]};
    sf::Vector2f shop_size{j_shop["shop_size"][0], window_sizeY};
    // sf::Vector2f shop_size{j_shop["shop_size"][0], j_shop["shop_size"][1]};
    sf::Vector2f btn_size{j_shop["btn_size"][0], j_shop["btn_size"][1]};
    sf::Vector2f shop_pos{window->getSize().x - shop_size.x, 0}; // gets changed in Game::load_map
    string texture_file{j_shop["texture_file"]}; // gets changed in Game::load_map
    json back_color = j_shop["background_color"];
    sf::Color color{back_color["r"], back_color["g"], back_color["b"]};
    json btn_color = j_shop["btn_color"];
    sf::Color button_color{btn_color["r"], btn_color["g"], btn_color["b"]};
    json btn_select_color = j_shop["btn_select_color"];
    sf::Color button_select_color{btn_select_color["r"], btn_select_color["g"], btn_select_color["b"]};
    json bcc = j_shop["btn_no_cash_color"];
    sf::Color button_no_cash_color{bcc["r"], bcc["g"], bcc["b"]};
    json fc = j_shop["font_color"];
    sf::Color font_color{fc["r"], fc["g"], fc["b"]};
    shop = Tower_shop{Tower::factory_towers, shop_pos, shop_size,btn_size, color,button_color,button_select_color, button_no_cash_color, font_color, font_name, texture_file};
    wallet.ui_callback = [&](Wallet w){shop.update_shop_ui(w);};
    shop.update_shop_ui(wallet);
    // cout << "wallet in game" << wallet.getCash() << endl;
}

int Game::get_frame()
{
    return frame;
}
void Game::update_frame() // OBS! dont use this or the game breaks!! why is this here?
{
    frame++;
}

sf::Vector2u Game::get_window_size()
{
    return window->getSize();
}

void Game::set_selected_map(std::string map_name)
{
    selected_map = map_name;
}

void Game::set_render_tower_radii(bool render)
{
    render_tower_radii = render;
}
bool Game::get_render_tower_radii()
{
    return render_tower_radii;
}

/* Check collisions between every enemy and projectile.
 * When collision happens we check if the enemy or projectile should be removed.
 */
void Game::check_collision()
{
    // variables to ease readability.
    vector<Enemy*> &enemies = Enemy::enemies;
    vector<Projectile*> &projectiles = Projectile::projectiles;
    Enemy *enemy;
    Projectile *projectile;

    for (size_t enemy_i = 0;
         enemy_i < enemies.size();
         )
    {
        enemy = enemies.at(enemy_i);
        for (size_t projectile_i = 0;
         projectile_i  < projectiles.size();
         )
        {
            projectile = projectiles.at(projectile_i);
            // check if enemy and projectile has collided
            if (collided_bb(projectile,enemy))
            {
                // check if enemy should be deleted
                if (enemy->collision(projectile))
                {
                    wallet.add(enemy->get_reward());
                    delete enemy;
                    enemy = nullptr;
                    // swap and pop for increased performance
                    if (enemies.size() > 1)
                    {
                        swap(enemies.at(enemy_i),enemies.back());
                    }
                    enemies.pop_back();
                }
                // check if projectile should be deleted
                if (projectile->collision())
                {
                    delete projectile;
                    projectile = nullptr;
                    if (projectiles.size() > 1)
                    {
                        swap(projectiles.at(projectile_i),projectiles.back());
                    }
                    projectiles.pop_back();
                }

                /* when true, enemy_i will not get updated. We do this because
                 * enemy_i will have the correct index for the next enemy we
                 * want to check since we did a swap.
                */
                if (!enemy)
                {
                    break;
                }
                // same here but for projectile
                if (!projectile)
                {
                    continue;
                }

            }
            projectile_i++;
        }
        /* if enemy is not nullptr no enemy has been deleted and we want to
         * update enemy_i
         */
        if (enemy)
        {
            enemy_i++;
        }

    }
}

void Game::check_collision_towers()
{
    float distance{};
    for (size_t tower_i = 0;
            tower_i < Tower::towers.size();
            tower_i++)
    {
        Tower::towers.at(tower_i)->shootable_enemies.clear();
        if (!dynamic_cast<Tower_ring*>( Tower::towers.at(tower_i) ) )
        {
            for (size_t enemy_i = 0;
                enemy_i < Enemy::enemies.size();
                enemy_i++)
            {
                        if (collided(Tower::towers.at(tower_i),
                                    Enemy::enemies.at(enemy_i),
                                    distance))
                        {
                            Tower::towers.at(
                                tower_i)->collision(Enemy::enemies.at(enemy_i),
                                distance);
                        }
            }
        }
    }
}

void Game::fire_towers()
{
    for (auto tower = Tower::towers.begin();
         tower != Tower::towers.end();
         tower++)
        {
            (*tower)->shoot();
        }
}

void Game::handle_input(sf::Event & event)
{
    // Has a mouse button been pressed?
    if ( event.type == sf::Event::MouseButtonPressed )
    {
        auto mouse { event.mouseButton };
        float mouseX = mouse.x;
        float mouseY = mouse.y;
        // Is it the left mouse button?
        if ( mouse.button == sf::Mouse::Button::Left )
        {
            handle_click(sf::Vector2f{mouseX, mouseY});
        }
        else if ( mouse.button == sf::Mouse::Button::Right)
        {
            handle_right_click(sf::Vector2f{mouseX, mouseY});
        }
    }
}

void Game::handle_right_click(sf::Vector2f click)
{
    if(!shop.getGlobalBounds().contains(click))
    {
        Tile *tile = Tile::get_tile_by_coord(click);
        Tile_tower *tile_t;
        if ( (tile_t = dynamic_cast<Tile_tower*>(tile)) )
        {
            tile_t->on_click(click);
        }
    }
}

 void Game::handle_click(sf::Vector2f click)
 {
     // Do we want to be smart or dumb here? One way is to just itterate over all
     // clickable object and see if they contain the clicked location. A faster
     // way is to use the fact that everything is in a grid and calculate what
     // button was pressed. I did the dump way.

     if(!shop.getGlobalBounds().contains(click))
     {
        Tower * tw = shop.get_chosen_tower();
        // cout << "Chosen tower in game: " << tw << endl;
        if(tw != nullptr && wallet.getCash() >= tw->cost)
        {
            Tile_tower * tile = dynamic_cast<Tile_tower*>(Tile::get_tile_by_coord(click));

            // cout << "Enough money to buy. Tile: " << tile << endl;
            if(tile != nullptr && !tile->is_occupied() && tile->on_click(tw))
            {
                wallet.take(tw->cost);
            }
        }

     }
     shop.on_click(click, wallet);
 }

void Game::update_logic()
{
    // if(Enemy::enemies.size() == 0 && wave_manager.all_enemies_have_spawned())
    // {
        // cout << "next_wave" << endl;
        // wave_manager.next_wave(frame, fps);
    // }
    wave_manager.spawn_enemies(frame);
    enemy_update_direction();
    enemy_update_position();

    if (Projectile::projectiles.size() > 0)
    {
        projectile_update_position();
    }
    check_collision();
    check_collision_towers();
    fire_towers();
    frame++;
}

int Game::get_health()
{
    return health.get_health();
}
