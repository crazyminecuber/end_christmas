#include "Tower.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include "Game.h"
using namespace std;

Tower_properties Tower_ring::tower_prop;
entity_properties Tower_ring::entity_prop;
Tower_properties Tower_basic::tower_prop{};
entity_properties Tower_basic::entity_prop{};
std::vector<Tower*> Tower::static_towers{};
std::vector<Entity*> Tower::shootable_enemies;
int Tower_ring::num_projectile_init{};

//Functions for the class Tower
Tower::Tower(Tower const & other) 
    : Entity(other), 
    fire_period{other.fire_period},
    fire_angle{other.fire_angle},
    projectile{other.projectile},
    cost{other.cost}
{

}

void Tower::collision(Entity* object)
{
  Tower::shootable_enemies.push_back(object);
  //shoot();
}

//Creating ptojectiles
void Tower::make_projectile(sf::Vector2f dir, sf::Vector2f pos)
{
    projectile->clone(dir,pos);
}

/*---------------------------------------------------------------------*/

//Tower_basic
Tower_basic::Tower_basic(Tower_basic const & other)
    : Tower(other)
{

}

//Making aktiv tower
void Tower_basic::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_basic{*this};
    t->setPosition(position);
    static_towers.push_back(t);
}

//Shoot if shootable_enemies and if fire_period
void Tower_basic::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (Game::get_frame() - frame_last_shot > tower_prop.fire_period_init)
    {
      Entity * target = select_target();
      //rotate_to_target(target);
      sf::Vector2f aim_dir = aim_direction(target);
      make_projectile(aim_dir, getPosition());
      frame_last_shot = Game::get_frame();
      shootable_enemies.clear();
    }
  }
}

//Selecting enemy to shoot at
Entity * Tower_basic::select_target()
{
  if (!shootable_enemies.empty())
  {
    target_enemy = shootable_enemies.front();
  }
  return target_enemy;
}

// void Tower_basic::rotate_to_target(Entity * target_enemy)
// {
//     float angle = (180 / M_PI) * atan((target_enemy->getPosition().y - getPosition().y)/
//                       (target_enemy->getPosition().x - getPosition().y));
//     setRotation(angle);
// }

//Selecting direction for projectile
sf::Vector2f Tower_basic::aim_direction(Entity * target_enemy)
{
  sf::Vector2f aim = (target_enemy->getPosition());
  sf::Vector2f t_dir = (target_enemy->get_direction() );
  sf::Vector2f dir {aim + t_dir - getPosition()};
  float length {sqrt(dir.x * dir.x + dir.y * dir.y)};
  //Normalize vector
  sf::Vector2f norm_dir{dir.x / length, dir.y / length};
  return norm_dir;
}
//----------------------------------------------------------------------------

//Tower_ring
Tower_ring::Tower_ring(Tower_ring const & other)
    : Tower(other), 
    num_of_projectile{other.num_of_projectile}
{

}

//Making aktiv tower
void Tower_ring::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_ring{*this};
    t->setPosition(position);
    static_towers.push_back(t);
}

//Function shoot in the class Tower_ring. Shoots in num_of_projectile number of directions.
void Tower_ring::shoot()
{
  if (!shootable_enemies.empty())
  {
  if(num_projectile_shoot < num_of_projectile)
    {
      if (Game::get_frame() - frame_last_shot > tower_prop.fire_period_init)
      {
        float rad = (2 * M_PI / num_of_projectile) * num_projectile_shoot;
        sf::Vector2f dir{cos(rad), sin(rad)};
        make_projectile(dir, getPosition());
        frame_last_shot = Game::get_frame();
        ++num_projectile_shoot;
      }
    }
    else
    {
      num_projectile_shoot=0;
    }
  }
}
