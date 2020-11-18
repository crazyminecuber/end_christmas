#include "Projectile.h"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

//Funktioner som tillhör Projectile
Projectile::Projectile()
{}

//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile(Projectile const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

//Next posistion
void Projectile::update_position()
  {
    position += mov_spd * dir;

  };

//Funktioner som tillhör Projectile_basic
Projectile::Projectile_basic()
{
  if(game.frame == frame_to_die)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile_basic(Projectile_basic const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile::collision(Entity* object)
  {
    delete *curr_proj;
  };
//Funktion som tillhör Projectile_pierce
Projectile::Projectile_pierce
{
  if(game.frame == frame_to_die)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile_pierce(Projectile_pierce const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile::collision(Entity* object)
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
  };

//Funktion som tillhör Projectile_bomb
Projectile::Projectile_bomb
{
if(game.frame == frame_to_die)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile_bomb(Projectile_bomb const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile::collision(Entity* object)
  {
    //delete in Enemy that will delete Enemy
    projectiles.add<new Projectile_bomb_blast*>;
    delete *curr_proj;
  };

//Funktion som tillhör Projectile_bomb_blast
Projectile::Projectile_bomb_blast
{
  if(game.frame == frame_to_die)
  {
    Projectile*->update_rad();
  }
  //delete projectile if beyond frame_to_die
  delete Projectile*;
}

//Kopieringskonstruktor som lägger in i lista
Projectile::Projectile_bomb_blast(Projectile_bomb_blast const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile::update_rad(Entity* object)
{
  Projectile.hit_rad += blast_rad;
};

void Projectile::collision(Entity* object)
{
  //delete in Enemy that will delete Enemy
  delete *curr_proj;
};
