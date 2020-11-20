#include "Tower.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

Tower::Tower(std::string texture_file, sf::Vector2f position,
      sf::Vector2f siz, float hit_rad,
      sf::Vector2f dir, float mov_spd, int arg_level){}


//Functions for the class Tower
void Tower::collision(Entity* object)
{
  Tower::shootable_enemies.push_back(object);
  Tower* shoot();
}

void Tower::make_projectile(sf::Vector2f velocity)
{
  Projectile* p = new Projectile{
          Projectile::prop.texture_file, //Texture
          Projectile::position_init, //Poistion
          Projectile::prop.size, //Size
          Projectile::prop.hit_rad,        //Hit_rad
          aim(),       //dir
          Projectile::prop.mov_spd,          //mov_spd
      };
      Projectile::projectiles.push_back(p);
};

//Functions for the class Tower_basic
Tower_basic::~Tower_basic(){}

void Tower_basic::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (frame_last_shot > fire_period)
    {
      Tower* select_target();
    }
  }
}

Entity Tower_basic::select_target()
{
  if (!shootable_enemies.empty())
  {
    target_enemy = shootable_enemies.front();
    float angel = cos((target_enemy->position.y- position.y)/
                      (target_enemy->position.x - position.y));
    if (!angel == 0)
    {
      Tower* setRotation(angle);
    }
  }
  return target_enemy;
}


sf::Vector2f Tower_basic::aim()
{
  target_enemy = select_target();
  sf::Vector2f aim = (target_enemy->position - position) +
                       (target_enemy->mov_spd * target_enemy->dir);
  return aim;
}

//Function shoot in the class Tower_ring.
Tower_ring::~Tower_ring(){}

void Tower_ring::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (frame_last_shot > fire_period)
    {
      Tower* rotate(fire_angel);
      Tower* make_projectile();
    }
  }
}
