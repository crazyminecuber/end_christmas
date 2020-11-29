#include "Tower.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

Tower_properties Tower_ring::tower_prop;
entity_properties Tower_ring::entity_prop;
Tower_properties Tower_basic::tower_prop{};
entity_properties Tower_basic::entity_prop{};
std::vector<Tower*> Tower::static_towers{};
int Tower_ring::num_projectile_init{8}; // Läsa in från fil istället?

//Functions for the class Tower
void Tower::collision(Entity* object)
{
  Tower::shootable_enemies.push_back(object);
}

void Tower_basic::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_basic{
        texture_file, position, size, hitbox_radius, direction, movement_speed, cost, projectile
    };
    static_towers.push_back(t);

}


// 2 alternativ passiva projektiler som skapar sig själva,
// eller en arg_level som avgör vilken typ av projektil som Tower skapar


void Tower::make_projectile(sf::Vector2f dir, sf::Vector2f pos)
{

    projectile->clone(dir,pos);
}




//Functions for the class Tower_basic

void Tower_basic::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (frame_last_shot > fire_period)
    {
      Entity * target = select_target();
      rotate_to_target(target);
      sf::Vector2f aim_dir = aim_direction(target);
      make_projectile(aim_dir, getPosition());
    }
  }
}

Entity * Tower_basic::select_target()
{
  if (!shootable_enemies.empty())
  {
    target_enemy = shootable_enemies.front();

  }
  return target_enemy;
}

void Tower_basic::rotate_to_target(Entity * target_enemy)
{
    float angle = (180 / M_PI) * atan((target_enemy->getPosition().y - getPosition().y)/
                      (target_enemy->getPosition().x - getPosition().y));
    setRotation(angle);
}


sf::Vector2f Tower_basic::aim_direction(Entity * target_enemy)
{
  // Beräknar var fienden kommer vara nästa frame och siktar dit.
  // Kan göras bättre genom att se fler frames frammåt genom att multiplicera
  // med en konstant (som beror av avståndet mellan fienden och tornet)
  sf::Vector2f aim = (target_enemy->getPosition() - getPosition()) +
                       (target_enemy->movement_speed * target_enemy->direction);
  //Normalize vector
  sf::Vector2f dir {aim - getPosition()};
  float length {sqrt(dir.x * dir.x + dir.y * dir.y)};

  sf::Vector2f norm_dir{dir.x / length, dir.y / length};
  return norm_dir;
}
//----------------------------------------------------------------------------

//Function shoot in the class Tower_ring.

void Tower_ring::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_ring{
        texture_file, position, size, hitbox_radius, direction, movement_speed, cost, num_of_projectile, projectile
    };
    static_towers.push_back(t);

}

// skall igentiligen skjuta num_of_projectile st skott på efter varandra, med några frames i mellan
// Blir ganska komplicerat att implementera så jag förslår att vi till en början
// skjuter 8 skott i samma frame.
void Tower_ring::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (frame_last_shot > fire_period)
    {
      for(int i = 0; i < num_of_projectile; i++)
      {
        float rad = (2 * M_PI / num_of_projectile) * i;
        sf::Vector2f dir{cos(rad), sin(rad)};
        make_projectile(dir, getPosition());

      }
    }
  }
}

