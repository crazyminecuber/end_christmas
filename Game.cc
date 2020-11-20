#include "Game.h"
#include <sstream>
#include <fstream>
#include <vector>
#include "json.hpp" // to parse data from json file. See json.hpp for source.
#include "Enemy_basic.h"
#include "Enemy_boss.h"
#include "Projectile.h"
#include "Tower.h"
#include <SFML/Graphics/Sprite.hpp> 
//#include "Resource_manager.h"

using namespace std;
using json = nlohmann::json;

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

void Game::load_map(string const & file)
{
    ifstream ifs(file);
    istringstream iss;
    string line;
    int num;
    vector<vector<int>> vec2{};

    if (ifs.is_open())
    {   
        while ( ifs.getline(line, size_t{255}))
        {
            vec2.push_back(vector<int>{});
            iss.str(line);
            while (iss >> num)
            {
                vec2.back().push_back(num);
            }
        } 
        int tile_size = window_height / vec2.size();
        for (int y = 0; y < vec2.size(); y++)
        {   
            for (int x = 0; x < vec2[y].size(); x++)
            {
                if (num == 0)
                {
                    new Tile_nothing(x-1,y-1,tile_size);
                }
                else if (num == 1)
                {
                    new Tile_enemy(x-1,y-1,tile_size);
                }
                else if (num == 2)
                {
                    new Tile_tower(x-1,y-1,tile_size);
                }
                else if (num == 3)
                {
                    new Tile_enemy_win(x-1,y-1,tile_size)
                }
                else if (num == 4)
                {
                    new Tile_enemy_start(x-1,y-1,tile_size);
                }
            }
        }
    }
    ifs.close();
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
    Tower_basic::cost_init = tower = tower["cost_init"];

    tower = json_obj["Tower_ring"];
    Tower_ring::detection_radius_init = tower["detection_radius_init"];
    Tower_ring::sprite_init.setTexture(resources.load(tower["sprite_init"]));
    Tower_ring::fire_period_init = tower["fire_period_init"];
    Tower_ring::projectile_init = get_tower_projectile(tower["projectile_init"]);
    Tower_ring::shop_sprite_init.setTexture(resources.load(tower["shop_sprite_init"]));
    Tower_ring::cost_init = tower = tower["cost_init"]
}

void check_collision()
{
    //kolla tower - enemy
    vector<Enemy*> *enemies = &Enemy::enemies;
    vector<Projectile*> *projectiles = &Projectile::projectiles;
    vector<Tower*> *towers = &Tower::static_towers;
    for (auto enemy_it = Enemy::enemies.begin(); 
         enemy_it != Enemy::enemies.end();
         enemy_it++)
    {
        // kolla kollision mellan projectile - enemy
        for (auto projectile_it = Projectile::projectiles.begin(); 
         projectile_it != Projectile::projectiles.end();
         projectile_it++)
        {
            if ((*projectile_it)->getPosition() 
                == (*enemy_it)->getPosition())
            {
                (*projectile_it)->collision(*enemy_it);
                (*enemy_it)->collision(*projectile_it);
                // här borde game ta bort objekten. Tas de bort i collision() så kommer den andra kollision inte att fungera.
                // Entity::check_if_kill() som dödar objektet om life<=0
            }
        }
        for (auto tower_it = Tower::static_towers.begin();
             tower_it != Tower::static_towers.end();
             tower_it++)
        {
            if ((*tower_it)->getPosition() 
                == (*enemy_it)->getPosition())
            {
                (*tower_it)->collision((*enemy_it));
            }
        }
    }
}
void fire_towers()
{
    for (auto tower = Tower::static_towers.begin();
         tower != Tower::static_towers.end(); 
         tower++)
        {
            (*tower)->shoot();
        }
}