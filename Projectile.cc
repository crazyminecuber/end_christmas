#include "Projectile.h"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

//Funktioner som tillhör Projectile
Projectile::Projectile(std::string texture_file, sf::Vector2f position,
      sf::Vector2f siz, float hit_rad, sf::Vector2f dir, float mov_spd):
      Entity(texture_file, position, siz, hit_rad, dir, mov_spd){}

Projectile::~Projectile(){}

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
Projectile_basic::Projectile_basic() : Projectile()
{
  if(game.frame == frame_to_die)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete *this;
}

Projectile_basic::~Projectile_basic(){}

//Kopieringskonstruktor som lägger in i lista
Projectile_basic::Projectile_basic(Projectile_basic const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile_basic::collision(Entity* object)
  {
    delete *this;
  };
//Funktion som tillhör Projectile_pierce
Projectile_pierce::Projectile_pierce() : Projectile()
{
  if(game.frame == frame_to_die)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete *this;
}

Projectile_pierce::~Projectile_pierce(){}

//Kopieringskonstruktor som lägger in i lista
Projectile_pierce::Projectile_pierce(Projectile_pierce const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile_pierce::collision(Entity* object)
  {
    //delete in Enemy that will delete Enemy
    if(nr_enemies_killed <= nr_pierce)
    {
      nr_enemies_killed+= 1;
    }
    else
    {
      delete *this;
    }
  };

//Funktion som tillhör Projectile_bomb
Projectile_bomb::Projectile_bomb() : Projectile()
{
if(game.frame == frame_to_die)
  {
    Projectile*->update_position();
  }
  //delete projectile if beyond frame_to_die
  delete *this;
}

Projectile_bomb::~Projectile_bomb(){}

//Kopieringskonstruktor som lägger in i lista
Projectile_bomb::Projectile_bomb(Projectile_bomb const& other)
{
  *this = other;
  projectiles.add(*this);
  frame_to_die() = game.frame + frames_to_live();
}

void Projectile_bomb::collision(Entity* object)
  {
    //delete in Enemy that will delete Enemy
    projectiles.add<new Projectile_bomb_blast*>;
    delete Projectile_bomb*;
  };

//Funktion som tillhör Projectile_bomb_blast
Projectile_bomb_blast::Projectile_bomb_blast() : Projectile()
{
  if(game.frame == frame_to_die)
  {
    Projectile->update_rad();
  }
  //delete projectile if beyond frame_to_die
  delete *this;
}

Projectile_bomb_blast::~Projectile_bomb_blast(){}

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
  delete *this;
};
