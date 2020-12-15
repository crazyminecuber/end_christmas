#include "Tower.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include "Game.h"
using namespace std;
//Init static variables
std::vector<Tower*> Tower::towers{};
std::vector<Tower*> Tower::factory_towers{};

//Functions for the class Tower
Tower::Tower(Tower const & other)
    : Entity(other),
    fire_period{other.fire_period},
    fire_angle{other.fire_angle},
    projectile{other.projectile},
    cost{other.cost}
{}

void Tower::init_circle_hit_rad()
{
    circle_hit_rad.setRadius(hitbox_radius);
    circle_hit_rad.setOrigin(circle_hit_rad.getGlobalBounds().width  / 2.f,
                             circle_hit_rad.getGlobalBounds().height / 2.f);
    circle_hit_rad.setFillColor(sf::Color(0, 0, 0, 40));
    circle_hit_rad.setOutlineColor(sf::Color::Black);
    circle_hit_rad.setOutlineThickness(2);
    circle_hit_rad.setPosition(getPosition());
}

void Tower::collision(Enemy* object)
{
  shootable_enemies.push_back(object);
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
{}

//Making active tower
Tower * Tower_basic::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_basic{*this};
    t->setPosition(position);
    t->init_circle_hit_rad();
    towers.push_back(t);
    return t;
}

//Shoot if shootable_enemies and if fire_period
void Tower_basic::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (Game::get_frame() - frame_last_shot > fire_period)
    {
      Entity * target = select_target();
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
{}

//Making aktiv tower
Tower * Tower_ring::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_ring{*this};
    t->setPosition(position);
    // t->init_circle_hit_rad(); // Not sure if hit_rad has any purpose for tower_rings?
    towers.push_back(t);
    return t;
}

//Function shoot in the class Tower_ring. Shoots in num_of_projectile number of directions.
void Tower_ring::shoot()
{
  if (Enemy::enemies.size() > 0)
  {
    if(num_projectile_shoot < num_of_projectile)
    {
        if (Game::get_frame() - frame_last_shot > fire_period)
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
