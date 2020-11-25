#include "Tower.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;


//Functions for the class Tower
void Tower::collision(Entity* object)
{
  Tower::shootable_enemies.push_back(object);
}


// 2 alternativ passiva projektiler som skapar sig själva,
// eller en arg_level som avgör vilken typ av projektil som Tower skapar

void Tower::make_projectile(sf::Vector2f direction)
{
    cout << "made projectile. Speed: " + to_string(direction.x);
    /*
  Projectile* p = new Projectile{
          Projectile::prop.texture_file, //Texture
          Projectile::position_init, //Poistion
          Projectile::prop.size, //Size
          Projectile::prop.hit_rad,        //Hit_rad
          aim(),       //dir
          Projectile::prop.mov_spd,          //mov_spd
      };
      Projectile::projectiles.push_back(p);
      */

}

//Functions for the class Tower_basic
Tower_basic::~Tower_basic(){}

void Tower_basic::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (frame_last_shot > fire_period)
    {
      select_target();
    }
  }
}

Entity * Tower_basic::select_target()
{
  if (!shootable_enemies.empty())
  {
    target_enemy = shootable_enemies.front();
    float angle = (180 / M_PI) * atan((target_enemy->getPosition().y - getPosition().y)/
                      (target_enemy->getPosition().x - getPosition().y));
    setRotation(angle);
  }
  return target_enemy;
}


sf::Vector2f Tower_basic::aim()
{
  target_enemy = select_target();
  // Beräknar var fienden kommer vara nästa frame och siktar dit.
  // Kan göras bättre genom att se fler frames frammåt genom att multiplicera
  // med en konstant (som beror av avståndet mellan fienden och tornet)
  sf::Vector2f aim = (target_enemy->getPosition() - getPosition()) +
                       (target_enemy->movement_speed * target_enemy->direction);
  return aim;
}

//Function shoot in the class Tower_ring.
Tower_ring::~Tower_ring(){}

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
        make_projectile(dir);

      }
    }
  }
}
