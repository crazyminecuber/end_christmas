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
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
};

void Projectile::update_position()
  {
    Projectile.position += Projectile.mov_spd * Projectile.dir;
  };

//Funktioner som tillhör Projectile_basic
Projectile::Projectile_basic()
{}

void Projectile::collision(Entity* object)
  {
    vector<Enemy*> enemies;
    vector<Projectile*> projectiles;
    for (auto curr_proj{projectiles.begin()}; curr_proj != projectiles.end(); ++curr_proj)
      {
        for (auto curr_enemy{enemies.begin()}; curr_enemy != enemies.end(); ++curr_enemy)
        {
          if (*curr_proj.hit_rad == *curr_enemy.hit_rad)
          {
            //delete in Enemy that will delete Enemy
            delete *curr_proj;
          }
        }
      }
  };
//Funktion som tillhör Projectile_pierce
Projectile::Projectile_pierce
{
  for(int a = 0; frame_to_die > a; a++)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

void Projectile::collision(Entity* object)
  {
  vector<Enemy*> enemies;
  vector<Projectile*> projectiles;
  int nr_enemies_killed = 0;
  for (auto curr_proj{projectiles.begin()}; curr_proj != projectiles.end(); ++curr_proj)
    {
      for (auto curr_enemy{enemies.begin()}; curr_enemy != enemies.end(); ++curr_enemy)
      {
        if (*curr_proj.hit_rad == *curr_enemy.hit_rad)
        {
          //delete in Enemy that will delete Enemy
          if(nr_enemies_killed <= nr_pierce)
          {
            //uppdate next enemy
          }
          else
          {
            delete *curr_proj;
          }
        }
      }
    }
  };

//Funktion som tillhör Projectile_bomb
Projectile::Projectile_bomb
{
  for(int a = 0; frame_to_die > a; a++)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

void Projectile::collision(Entity* object)
  {
  vector<Enemy*> enemies;
  vector<Projectile*> projectiles;
  for (auto curr_proj{projectiles.begin()}; curr_proj != projectiles.end(); ++curr_proj)
    {
      for (auto curr_enemy{enemies.begin()}; curr_enemy != enemies.end(); ++curr_enemy)
      {
        if (*curr_proj.hit_rad == *curr_enemy.hit_rad)
        {
          //delete in Enemy that will delete Enemy
          projectiles.add<new Projectile_bomb_blast*>;
          delete *curr_proj;
        }
      }
    }

  };

//Funktion som tillhör Projectile_bomb_blast
Projectile::Projectile_bomb_blast
{
  for(int a = 0; frame_to_die > a; a++)
  {
    Projectile*->update_radius();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

void Projectile::update_radius(Entity* object)
{
  Projectile.hit_rad += blast_rad;
};

void Projectile::collision(Entity* object)
{
  vector<Enemy*> enemies;
  vector<Projectile*> projectiles;
  for (auto curr_proj{projectiles.begin()}; curr_proj != projectiles.end(); ++curr_proj)
    {
      for (auto curr_enemy{enemies.begin()}; curr_enemy != enemies.end(); ++curr_enemy)
      {
        if (*curr_proj.hit_rad == *curr_enemy.hit_rad)
        {
          //delete in Enemy that will delete Enemy
          delete *curr_proj;
        }
      }
    }

  }
