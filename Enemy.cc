#include "Enemy.h"
#include "Enemy_basic.h"
#include "Enemy_boss.h"
#include <SFML/Graphics.hpp>

void Enemy::set_direction(sf::Vector2f dir)
{
    direction = dir;
}
//Static
Enemy* Enemy::get_new_enemy_basic()
{
    Enemy_basic* e = new Enemy_basic{
        Enemy_basic::prop.texture_file, //Texture
        Enemy_basic::position_init, //Poistion
        Enemy_basic::prop.size, //Size
        Enemy_basic::prop.hit_rad,        //Hit_rad
        Enemy_basic::prop.dir,       //dir
        Enemy_basic::prop.mov_spd,          //mov_spd
        Enemy_basic::life_init           //life
    };
    return e;
}

Enemy* Enemy::get_new_enemy_boss()
{
    Enemy_boss* e = new Enemy_boss{
        Enemy_boss::prop.texture_file, //Texture
        Enemy_boss::position_init, //Poistion
        Enemy_boss::prop.size, //Size
        Enemy_boss::prop.hit_rad,        //Hit_rad
        Enemy_boss::prop.dir,       //dir
        Enemy_boss::prop.mov_spd,          //mov_spd
        Enemy_boss::life_init           //life
    };
    return e;
}

void Enemy::create_enemy_by_obj(Enemy* enemy)
{
    Enemy::enemies.push_back(enemy->clone());
}


void Enemy::new_basic()
{
    Enemy_basic* e = new Enemy_basic{
        Enemy_basic::prop.texture_file, //Texture
        Enemy_basic::position_init, //Poistion
        Enemy_basic::prop.size, //Size
        Enemy_basic::prop.hit_rad,        //Hit_rad
        Enemy_basic::prop.dir,       //dir
        Enemy_basic::prop.mov_spd,          //mov_spd
        Enemy_basic::life_init           //life
    };
    Enemy::enemies.push_back(e);
}

void Enemy::new_basic(sf::Vector2f position)
{
    Enemy_basic* e = new Enemy_basic{
        Enemy_basic::prop.texture_file, //Texture
        position, //Poistion
        Enemy_basic::prop.size, //Size
        Enemy_basic::prop.hit_rad,        //Hit_rad
        Enemy_basic::prop.dir,       //dir
        Enemy_basic::prop.mov_spd,          //mov_spd
        Enemy_basic::life_init           //life
    };
    Enemy::enemies.push_back(e);
}

void Enemy::new_boss()
{
    Enemy_boss* e = new Enemy_boss{
        Enemy_boss::prop.texture_file, //Texture
        Enemy_boss::position_init, //Poistion
        Enemy_boss::prop.size, //Size
        Enemy_boss::prop.hit_rad,        //Hit_rad
        Enemy_boss::prop.dir,       //dir
        Enemy_boss::prop.mov_spd,          //mov_spd
        Enemy_boss::life_init           //life
    };
    Enemy::enemies.push_back(e);
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
sf::Vector2f Enemy::position_init;
