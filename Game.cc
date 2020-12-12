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
#include "Tower_shop.h"
#include "Wave_manager.h"

using namespace std;
using json = nlohmann::json;
int Game::frame =0;


// Help function to determine init projectile for tower
Projectile* Game::get_tower_projectile(std::string const & projectile)
{

    sf::Vector2f double0{0,0};//7
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
// Help function to determine if object1 and object2 have collided
bool Game::collided(Entity const *object1, Entity const *object2)
{
    return (pow(object1->getPosition().x - object2->getPosition().x,2)
            < pow(object1->get_hitbox_radius() - object2->get_hitbox_radius(),2)
            && pow(object1->getPosition().y - object2->getPosition().y,2)
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
                    map_tiles[selected_map]["0"], window, tile_index_pos);
            }
            else if ( num == 1 )
            {
                Tile::tiles[tile_index_pos] = new Tile_tower(
                    map_tiles[selected_map]["1"], window, tile_index_pos);
            }
            else if ( num == 2 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy(
                    map_tiles[selected_map]["2"], window, tile_index_pos);
            }
            else if ( num == 3 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy_start(
                    map_tiles[selected_map]["3"], window, tile_index_pos);
            }
            else if ( num == 4 )
            {
                Tile::tiles[tile_index_pos] = new Tile_enemy_end(
                    map_tiles[selected_map]["4"], window, tile_index_pos);
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
    int tiles_per_col = tile_index_pos.x + (1 - 2);
    int tiles_per_row = tile_index_pos.y  + (1 - 2);
    Tile::side_length = std::min(window_size.x/tiles_per_col,
                                 window_size.y/tiles_per_row);
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

    shop.render(window, wallet);
    // render health
    health.render();
    wave_manager.render();
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
      if(!((*it)->update_position(window.getSize())))
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
    wave_manager.next_wave(frame, Game::fps);
}

int Game::get_current_wave() const
{
    return wave_manager.get_current_wave();
}

void Game::load_entities(string const & file_entity)
{
    ifstream ifs(file_entity);
    if (ifs.is_open())
    {
        json j_data;
        ifs >> j_data;
        init_enemies(j_data["Enemy"]);
        init_projectiles(j_data["Projectile"]);
        init_towers(j_data["Tower"]);
        init_shop(j_data["Shop"]);
        init_waves(j_data["Waves"]);
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
    Enemy_basic::reward_init = enemy_basic["reward_init"];
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
    Enemy_boss::reward_init = enemy_boss["reward_init"];
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
                          wave.value()["num_of_groups_inc"]));
    }
    // cout << wave.key() << endl;
    wave_manager.init_waves(frame, fps);
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

    proj = json_obj["Projectile_pierce"];
    Projectile_pierce::frames_to_live = proj["frames_to_live"];
    Projectile_pierce::damage_init = proj["damage_init"];
    Projectile_pierce::prop.texture_file = proj["texture"];
    Projectile_pierce::prop.size = sf::Vector2f(proj["size"][0],proj["size"][1]);
    Projectile_pierce::prop.hit_rad = proj["hit_rad"];
    Projectile_pierce::prop.dir = sf::Vector2f(0,0);
    Projectile_pierce::prop.mov_spd = proj["mov_spd"];
    Projectile_pierce::nr_pierce_init = proj["nr_pierce_init"];

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
    Tower_ring::tower_prop.projectile_init = get_tower_projectile(tower["projectile_init"]);
    Tower_ring::tower_prop.cost_init = tower["cost_init"];
    Tower_ring::tower_prop.fire_period_init = tower["fire_period_init"];
    Tower_ring::entity_prop.texture_file = tower["sprite_init"];
    Tower_ring::entity_prop.size = sf::Vector2f{tower["size"][0], tower["size"][1]};
    Tower_ring::entity_prop.hit_rad = tower["detection_radius_init"];
    Tower_ring::entity_prop.dir = sf::Vector2f{0, 0}; //Will be set by tile
    Tower_ring::entity_prop.mov_spd = 0;
    Tower_ring::num_projectile_init = tower["num_projectile_init"];

}

void Game::init_shop(json const & j_shop)
{
    wallet = Wallet{j_shop["start_cash"]};
    string font_name{j_shop["font_name"]};
    sf::Vector2f shop_size{j_shop["shop_size"][0], j_shop["shop_size"][1]};
    sf::Vector2f btn_size{j_shop["btn_size"][0], j_shop["btn_size"][1]};
    sf::Vector2f shop_pos{window.getSize().x - shop_size.x, 0};
    json back_color = j_shop["background_color"];
    sf::Color color{back_color["r"], back_color["g"], back_color["b"]};
    json btn_color = j_shop["btn_color"];
    sf::Color button_color{btn_color["r"], btn_color["g"], btn_color["b"]};
    json btn_select_color = j_shop["btn_select_color"];
    sf::Color button_select_color{btn_select_color["r"], btn_select_color["g"], btn_select_color["b"]};
    json bcc = j_shop["btn_no_cash_color"];
    sf::Color button_no_cash_color{bcc["r"], bcc["g"], bcc["b"]};
    vector<Tower *> passive_towers{new Tower_basic{}, new Tower_ring{}};
    shop = Tower_shop{passive_towers, shop_pos, shop_size,btn_size, color,button_color,button_select_color, button_no_cash_color,font_name};
    wallet.ui_callback = [&](Wallet w){shop.update_shop_ui(w);};
    shop.update_shop_ui(wallet);
    cout << "wallet in game" << wallet.getCash() << endl;
}

int Game::get_frame()
{
    return frame;
}
double Game::get_fps()
{
    return fps;
}

void Game::set_selected_map(std::string map_name)
{
    selected_map = map_name;
}

void Game::check_collision()
{
    vector<Enemy*> &enemies = Enemy::enemies;
    vector<Projectile*> &projectiles = Projectile::projectiles;
    bool enemy_deleted{false};
    bool projectile_deleted{false};
    Enemy *enemy;
    Projectile *projectile;
    for (size_t enemy_i = 0;
         enemy_i < enemies.size();
         )
    {
        enemy = enemies.at(enemy_i);
        // kolla kollision mellan projectile - enemy
        for (size_t projectile_i = 0;
         projectile_i  < projectiles.size();
         )
        {
            projectile = projectiles.at(projectile_i);
            if (collided_bb(projectile,enemy))
            {
                if (enemy->collision(projectile))
                {
                    wallet.add(enemy->get_reward());
                    delete enemy;
                    if (enemies.size() > 1)
                    {
                        swap(enemies.at(enemy_i),enemies.back());
                    }
                    enemies.pop_back();
                    enemy_deleted = true;
                }
                if (projectile->collision())
                {
                    delete projectile;
                    if (projectiles.size() > 1)
                    {
                        swap(projectiles.at(projectile_i),projectiles.back());
                    }
                    projectiles.pop_back();
                    projectile_deleted = true;
                }

                // when true, enemy_i will not get updated. We do this because enemy_i will have the correct index for the next enemy we want to check since the list is resized.
                if (enemy_deleted)
                {
                    enemy_deleted = false;
                    projectile_deleted = false;
                    goto next_enemy;
                }
                // same here but for projectile
                if (projectile_deleted)
                {
                    projectile_deleted = false;
                    goto next_projectile;
                }

            }
            projectile_i++;
            next_projectile:
            // statement needed after goto label
            cout << "";
        }
        enemy_i++;
        next_enemy:
        cout << "";
    }
}

void Game::check_collision_towers()
{
    for (size_t enemy_i = 0;
         enemy_i < Enemy::enemies.size();
         enemy_i++)
    {
        for (size_t tower_i = 0;
                tower_i < Tower::static_towers.size();
                tower_i++)
        {
            if (collided(Tower::static_towers.at(tower_i),
                        Enemy::enemies.at(enemy_i)))
            {
                Tower::static_towers.at(
                    tower_i)->collision(Enemy::enemies.at(enemy_i));
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

void Game::handle_input(sf::Event & event)
{
    // Has a mouse button been pressed?
    if ( event.type == sf::Event::MouseButtonPressed )
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

 void Game::handle_click(sf::Vector2f click)
 {
     // Do we want to be smart or dumb here? One way is to just itterate over all
     // clickable object and see if they contain the clicked location. A faster
     // way is to use the fact that everything is in a grid and calculate what
     // button was pressed. I did the dump way.

     if(!shop.getGlobalBounds().contains(click))
     {
        Tower * tw = shop.get_chosen_tower();
        cout << "Chosen tower in game: " << tw << endl;
        if(tw != nullptr && wallet.getCash() >= tw->cost)
        {
            Tile* tile = Tile::get_tile_by_coord(click);

            cout << "Enough money to buy. Tile: " << tile << endl;
            if(tile!= nullptr &&tile->on_click(tw))
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
