#include "Game.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include "json.hpp" // to parse data from json file. See json.hpp for source.
//#include "Enemy.h"
#include "Projectile.h"
#include "Tower.h"
#include <SFML/Graphics/Sprite.hpp> 
//#include "Resource_manager.h"

using namespace std;
using json = nlohmann::json;

void Game::load_map(string const & file)
{
    ifstream ifs(file);
    istringstream iss;
    string line;
    int num;
    if (ifs.is_open())
    {
        for (int y = -1; ifs.getline(line, '\n'); y++)
        {   
            iss.str(line);
            for (int x = -1; iss >> num; x++)
            {
                if (num == 0)
                {
                    Tile::tiles.push_back(new Tile_nothing(x,y));
                }
                else if (num == 1)
                {
                    Tile::tiles.push_back(new Tile_enemy(x,y));
                }
                else if (num == 2)
                {
                    Tile::tiles.push_back(new Tile_tower(x,y));
                }
                else if (num == 3)
                {
                    Tile::tiles.push_back(new Tile_enemy_win(x,y));
                }
                else if (num == 4)
                {
                    Tile::tiles.push_back(new Tile_enemy_start(x,y));
                }
            }
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
        init_enemies(j_data["Enemies"]);
        init_projectiles(j_data["Projectiles"]);
        init_towers(j_data["Towers"]);
    }
    ifs.close();
}

void Game::init_enemies(json const & json_obj)
{
    json enemy = json_obj["Enemy_basic"];
    Enemy_basic::life_init = enemy["life_init"];
    
    json enemy = json_obj["Enemy_boss"];
    Enemy_boss::life_init = enemy["life_init"];

}

void Game::init_projectiles(json const & json_obj)
{
    json proj = json_obj["Projectile_basic"];
    Projectile_basic::frames_to_live = proj["frames_to_live"];
    Projectile_basic::damage_init = proj["damage_init"];

    proj = json_obj["Projectile_pierce"];
    Projectile_basic::frames_to_live = proj["frames_to_live"];
    Projectile_basic::damage_init = proj["damage_init"];
    
    proj = json_obj["Projectile_bomb"];
    Projectile_basic::frames_to_live = proj["frames_to_live"];
    Projectile_basic::damage_init = proj["damage_init"];
    
    proj = json_obj["Projectile_bomb_blast"];
    Projectile_basic::frames_to_live = proj["frames_to_live"];
    Projectile_basic::damage_init = proj["damage_init"];
}

void Game::init_towers(json const & json_obj)
{
    json tower = json_obj["Tower_basic"];
    Tower_basic::detection_radius_init = tower["detection_radius_init"];
    Tower_basic::sprite_init.setTexture(resources.load(tower["sprite_init"]));
    Tower_basic::fire_period_init = tower["fire_period_init"];
    Tower_basic::projectile_init = get_tower_projectile(tower["projectile_init"]);
    Tower_basic::shop_sprite_init.setTexture(resources.load(tower["shop_sprite_init"]));
    Tower_basic::cost_init = tower = tower["cost_init"]

    tower = json_obj["Tower_ring"];
    Tower_ring::detection_radius_init = tower["detection_radius_init"];
    Tower_ring::sprite_init.setTexture(resources.load(tower["sprite_init"]));
    Tower_ring::fire_period_init = tower["fire_period_init"];
    Tower_ring::projectile_init = get_tower_projectile(tower["projectile_init"]);
    Tower_ring::shop_sprite_init.setTexture(resources.load(tower["shop_sprite_init"]));
    Tower_ring::cost_init = tower = tower["cost_init"]
}

Projectile* get_tower_projectile(string const & projectile)
{
    if(projectile == "Projectile_basic")
    {
        return new Projectile_basic{};
    }
    else if(projectile == "Projectile_pierce")
    {
        return new Projectile_pierce{};
    }
    else if(projectile == "Projectile_bomb")
    {
        return new Projectile_bomb{};
    }
}