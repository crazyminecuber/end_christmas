#include "Projectile.h"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

//Funktioner som tillhör Projectile
Projectile::Projectile()
{
  for(int a = 0; frame_to_die > a; a++)
  {
    //Uppdate position?
  }
  //delete projectile if beyond frame_to_die
  delete Projectile;
}

void Projectile::update_position()
  {
    Projectile.position += Projectile.mov_spd * Projectile.dir;
  }

//Funktioner som tillhör Projectile_basic
Projectile::Projectile_basic()
{}

void Projectile::collision(Entity* object)
  {
    vector<Object> objs = projectiles;
    objs.insert = enemies;

    for (auto curr{objs.begin()}; curr != objs.end(); ++curr)
      {
        for (auto next{curr+1}; next != objs.end(); ++next)
        {
          if (collide(*curr, *next))
          {
            // två? objekt har kolliderat
          }
        }
      }

//Funktion som tillhör Projectile_pierce
Projectile::Projectile_pierce
{}

void Projectile::collision(Entity* object)
  {

  }

//Funktion som tillhör Projectile_bomb
Projectile::Projectile_bomb
{}

void Projectile::collision(Entity* object)
  {
    
  }

//Funktion som tillhör Projectile_bomb_blast
Projectile::Projectile_bomb_blast
{}

void Projectile::collision(Entity* object)
  {

  }
