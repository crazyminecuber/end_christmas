#include "Projectile.h"
//#include <iostream>
#include <string>
#include <vector>
#include "Game.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

using namespace std;

//Tillhör klass Projectile
vector<Projectile*> Projectile::projectiles;

//Next posistion
bool Projectile::update_position()
    {
        if (Game::get_frame() < frame_to_die)
        {
            move(direction*movement_speed);
            return true;
        }
        else
        {
          return false;
        }
    }

//Kopieringskonstruktor
Projectile::Projectile(Projectile const& other):Entity(other)
{
  damage = other.damage;
  frame_to_die = other.frame_to_die;
}

//Tillhör Projectile_basic
entity_properties Projectile_basic::prop;
int Projectile_basic::frames_to_live;
int Projectile_basic::damage_init;

Projectile_basic::Projectile_basic(sf::Vector2f position,sf::Vector2f direction)
  : Projectile
    (
      prop.texture_file,
      position,
      prop.size,
      prop.hit_rad,
      direction,
      prop.mov_spd,
      damage_init
    )
{}
//Kopieringskonstruktor som lägger in i lista
Projectile_basic::Projectile_basic(Projectile_basic const& other)
    : Projectile(other)
{
    frame_to_die = Game::get_frame() + frames_to_live;
}
//clone and add direction void clone(sf::Vector2f direction, sf::Vector2f position)
void Projectile_basic::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_basic* p = new Projectile_basic{*this};
  p->direction = dir;
  p->setPosition(pos);
  projectiles.push_back(p);
}
//Removes and delete the porjectile when collided with an enemy
bool Projectile_basic::collision()
    {
      //Will be deleted on the next update_position
      return true;

    }


//Tillhör Projectile_pierce
entity_properties Projectile_pierce::prop;
int Projectile_pierce::frames_to_live;
int Projectile_pierce::damage_init;
int Projectile_pierce::nr_pierce;


Projectile_pierce::Projectile_pierce
(
  sf::Vector2f position,
  sf::Vector2f direction
)
  : Projectile
    (
      prop.texture_file,
      position,
      prop.size,
      prop.hit_rad,
      direction,
      prop.mov_spd,
      damage_init
    )
{}
//Kopieringskonstruktor som lägger in i lista
Projectile_pierce::Projectile_pierce(Projectile_pierce const& other)
    : Projectile(other)
{
    frame_to_die = Game::get_frame() + frames_to_live;
}
//clone and add direction
void Projectile_pierce::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_pierce* p = new Projectile_pierce{*this};
  p->direction = dir;
  p->setPosition(pos);
  projectiles.push_back(p);
}
//Counts nr of enemies killed and remove and delete the projectile when
// nr_pierce nr of enemies is killed
bool Projectile_pierce::collision()
{
    //delete in Enemy that will delete Enemy
    if(nr_enemies_killed <= nr_pierce)
    {
        nr_enemies_killed+= 1;
        return false;
    }
    else
    {
      //Will be deleted on the next update_position
      return true;
    }
}


//Funktion som tillhör Projectile_bomb
entity_properties Projectile_bomb::prop;
int Projectile_bomb::frames_to_live;
int Projectile_bomb::damage_init;

entity_properties Projectile_bomb_blast::prop;
int Projectile_bomb_blast::frames_to_live;
int Projectile_bomb_blast::damage_init;

Projectile_bomb::Projectile_bomb
  (
    sf::Vector2f position,
    sf::Vector2f direction
  )
    : Projectile
      (
        prop.texture_file,
        position,
        prop.size,
        prop.hit_rad,
        direction,
        prop.mov_spd,
        damage_init
      ),
      blast{}
  {

  }
//Kopieringskonstruktor som lägger in i lista
Projectile_bomb::Projectile_bomb(Projectile_bomb const& other)
    : Projectile(other), blast{other.blast}
{
  frame_to_die = Game::get_frame() + frames_to_live;
}
//clone and add direction
void  Projectile_bomb::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_bomb* p = new Projectile_bomb{*this};
  p->direction = dir;
  p->setPosition(pos);
  projectiles.push_back(p);
}

//adds bomb_blast to projectiles vector and remove and delete the projectile
bool Projectile_bomb::collision()
{
  blast.clone(sf::Vector2f(0,0), getPosition());
  //Will be deleted on the next update_position
  return true;
}


// Gör om bomb_blast så att den endast innehåller rad, texture, mm,
//Funktion som tillhör Projectile_bomb_blast
Projectile_bomb_blast::Projectile_bomb_blast()
    : Projectile
      (
        prop.texture_file,
        sf::Vector2f(0,0),
        prop.size,
        prop.hit_rad,
        direction,
        prop.mov_spd,
        damage_init
      )
  {}

Projectile_bomb_blast::Projectile_bomb_blast(string texture_file, sf::Vector2f position,
      sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd)
      : Projectile(texture_file, position, size, hit_rad, dir, mov_spd, damage_init){}

//Kopieringskonstruktor som lägger in i lista
Projectile_bomb_blast::Projectile_bomb_blast(Projectile_bomb_blast const& other)
    : Projectile(other)
{
  frame_to_die = Game::get_frame() + frames_to_live;
}

void Projectile_bomb_blast::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_bomb_blast *p = new Projectile_bomb_blast{*this};
  p->direction = dir;
  p->setPosition(pos);
  projectiles.push_back(p);
}

//remove and delete the projectile when collided with enemies
bool Projectile_bomb_blast::collision()
{
    //delete in Enemy that will delete Enemy
    //Will be deleted on the next update_position
    return false;
}
