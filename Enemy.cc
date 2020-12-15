#include "Enemy.h"
#include "Enemy_basic.h"
#include "Enemy_boss.h"
#include "json.hpp"
#include <SFML/Graphics.hpp>
#include <string>

Enemy* Enemy::get_new_enemy(nlohmann::json const & enemies, std::string chosen_enemy, sf::Vector2f position_init)
{
    Enemy* enemy;
    nlohmann::json enemy_props = enemies[chosen_enemy];
    if(enemy_props["type"] == "Enemy_basic")
    {
        enemy = Enemy::get_new_enemy_basic(enemy_props, position_init);
    }
    else if(enemy_props["type"] == "Enemy_boss")
    {
        Enemy* child = Enemy::get_new_enemy(enemies, enemy_props["child"], position_init);
        enemy = Enemy::get_new_enemy_boss(enemy_props, position_init, child);
    }
    return enemy;
}

Enemy* Enemy::get_new_enemy_basic(nlohmann::json const & enemy_props, sf::Vector2f position_init)
{
    std::string texture_init = enemy_props["texture"];
    sf::Vector2f size_init;
    size_init.x = enemy_props["size"][0];
    size_init.y = enemy_props["size"][1];
    float hit_rad_init = enemy_props["hit_rad"];
    sf::Vector2f dir_init{0,0};
    float mov_spd_init = enemy_props["mov_spd"];
    int life_init = enemy_props["life_init"];
    int reward_init = enemy_props["reward_init"];
    Enemy_basic* e = new Enemy_basic{
        texture_init, //Texture
        position_init, //Poistion
        size_init, //Size
        hit_rad_init,        //Hit_rad
        dir_init,       //dir
        mov_spd_init,          //mov_spd
        life_init,
        reward_init
    };
    return e;
}

Enemy* Enemy::get_new_enemy_boss(nlohmann::json const & enemy_props,
                                sf::Vector2f position_init, Enemy* child)
{
    std::string texture_init = enemy_props["texture"];
    sf::Vector2f size_init;
    size_init.x = enemy_props["size"][0];
    size_init.y = enemy_props["size"][1];
    float hit_rad_init = enemy_props["hit_rad"];
    sf::Vector2f dir_init{0,0};
    float mov_spd_init = enemy_props["mov_spd"];
    int life_init = enemy_props["life_init"];
    int reward_init = enemy_props["reward_init"];
    int num_of_children = enemy_props["num_of_children"];

    Enemy_boss* e = new Enemy_boss{
        texture_init,   //Texture
        position_init,  //Position
        size_init,      //Size
        hit_rad_init,   //Hit_rad
        dir_init,       //dir
        mov_spd_init,   //mov_spd
        life_init,
        reward_init,
        num_of_children,
        child
    };
    return e;
}

void Enemy::create_enemy_by_obj(Enemy* enemy)
{
    Enemy::enemies.push_back(enemy);
}

void Enemy::delete_all_enemies()
{
    for (auto p : Enemy::enemies)
    {
        delete p;
    }
    Enemy::enemies.clear();
}

int Enemy::get_damage()
{
    return life;
}

std::vector<Enemy*> Enemy::enemies;
