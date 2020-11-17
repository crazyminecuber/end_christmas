#inlcude "Tower.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Tower::Tower(std::string texture_file, sf::Vector2f position,
      sf::Vector2f siz, float hit_rad,
      sf::Vector2f dir, float mov_spd, int arg_level){}
Tower::~Tower(){}

//Functions for the class Tower
void Tower::collision(Entity* object)
{
  vector<Tower*> towers{};
  vector<Enemy*> enemies{};
  for (auto curr_tower{towers.begin()}; curr_tower != towers.end(); ++curr_tower)
      for (auto curr_enemy{enemies.begin()}; curr_enemy != enemies.end(); ++curr_enemy)
      {
        if (*curr_tower.hit_rad == *curr_enemy.hit_rad))
        {
          curr_tower->shoot();
        }
      }
  };

void Tower::shoot()
{
  if (!shootable_enemies.empty())
  {
    arg_level.make_projectile();
  }
};

void Tower::make_projectile(Vector2f velocity)
{
  new Projectiles*;
};

//Functions for the class Tower_basic
void Tower_basic::shoot()
{

};

Entity Tower_basic::select_target()
{
  if (!shootable_enemies.empty())
  {
    std::string target_enemy = shootable_enemies[1];
  }
  return target_enemy;
};

vector2<float> Tower_basic::aim()
{

};

//Functions for the class Tower_ring
void Tower_ring::shoot()
{

};
