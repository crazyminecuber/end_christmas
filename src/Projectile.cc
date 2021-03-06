#include "Projectile.h"
#include "Game.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using namespace std;

//Projectile
//Static Projectile
vector<Projectile*> Projectile::projectiles;

//Update position and return true if its still alive or false if frame>frame_to_die
bool Projectile::outside_screen(sf::Vector2u const & window_size)
{
  bool x{0 > getPosition().x || getPosition().x > window_size.x};
  bool y{0 > getPosition().y || getPosition().y > window_size.y};
  return x || y;
}
bool Projectile::update_position(sf::Vector2u const & window_size)
{
    if (Game::get_frame() <= frame_to_die && !(outside_screen(window_size)))
    {
        move(direction*movement_speed);
        return true;
    }
    else
    {
      return false;
    }
}


//Copy-constructor, sets frame_to_die and damage
Projectile::Projectile(Projectile const& other):Entity(other)
{
  damage = other.damage;
  frame_to_die = other.frame_to_die;
  rotation_offset = other.rotation_offset;
}

/*----------------------------------------------------------------------------*/
//Projectile_basic
//statis Projectile_basic
entity_properties Projectile_basic::prop;
int Projectile_basic::frames_to_live;
int Projectile_basic::damage_init;
float Projectile_basic::rotation_offset_init;

Projectile_basic::Projectile_basic(sf::Vector2f position,sf::Vector2f direction)
  : Projectile
  (
    prop.texture_file,
    position,
    prop.size,
    prop.hit_rad,
    direction,
    prop.mov_spd,
    damage_init,
    rotation_offset_init
  )
{}

//Copy-constructor, sets frame_to_die
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

// Returns true if the porjectile should be deleted when collided with an enemy
bool Projectile_basic::collision()
{
  return true;
}

/*----------------------------------------------------------------------------*/
//Projectile_pierce
//static Projectile_pierce
entity_properties Projectile_pierce::prop;
int Projectile_pierce::frames_to_live;
int Projectile_pierce::damage_init;
int Projectile_pierce::nr_pierce_init;
float Projectile_pierce::rotation_offset_init;

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
      damage_init,
      rotation_offset_init
    ),
    nr_pierce{nr_pierce_init}
{}

//Copy-constructor, sets frame_to_die
Projectile_pierce::Projectile_pierce(Projectile_pierce const& other)
    : Projectile(other)
{
    frame_to_die = Game::get_frame() + frames_to_live;
}

//Clone and add to vector projectiles
void Projectile_pierce::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_pierce* p = new Projectile_pierce{*this};
  p->direction = dir;
  p->setPosition(pos);

  //OBS in math, radians are used and its anticlockwise. In sfml, degrees are
  //used and its clockwise since y is pointing downwards.
  float degree = (180 / M_PI) * atan2(dir.y, dir.x) + rotation_offset;
  p->setRotation(degree);

  projectiles.push_back(p);
}

//Counts nr of enemies killed and return true if the projectile should be delete
//when nr_pierce nr of enemies is killed
bool Projectile_pierce::collision()
{
  nr_enemies_killed+= 1;
  if(nr_enemies_killed < nr_pierce_init)
  {
      return false;
  }
  else
  {
    return true;
  }
}


/*----------------------------------------------------------------------------*/
//Projectile_bomb
//Static Projectile_bomb
entity_properties Projectile_bomb::prop;
int Projectile_bomb::frames_to_live;
int Projectile_bomb::damage_init;
float Projectile_bomb::rotation_offset_init;
//static Projectile_bomb_blast
entity_properties Projectile_bomb_blast::prop;
int Projectile_bomb_blast::frames_to_live;
int Projectile_bomb_blast::damage_init;
float Projectile_bomb_blast::rotation_offset_init;

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
        damage_init,
        rotation_offset_init
      ),
      blast{}
  {}


//copy-constructor, copy blast and sets frame_to_die
Projectile_bomb::Projectile_bomb(Projectile_bomb const& other)
    : Projectile(other), blast{other.blast}
{
  frame_to_die = Game::get_frame() + frames_to_live;
}

//clone and adds to vector projectiles
void  Projectile_bomb::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_bomb* p = new Projectile_bomb{*this};
  p->direction = dir;
  p->setPosition(pos);
  projectiles.push_back(p);
}

//Clone object blast and return true when the projectile should be delete
//when collided
bool Projectile_bomb::collision()
{
  blast.clone(sf::Vector2f(0,0), getPosition());
  return true;
}


/*----------------------------------------------------------------------------*/

// Projectile_bomb_blast
Projectile_bomb_blast::Projectile_bomb_blast()
    : Projectile
      (
        prop.texture_file,
        sf::Vector2f(0,0),
        prop.size,
        prop.hit_rad,
        direction,
        prop.mov_spd,
        damage_init,
        rotation_offset_init
      )
  {}

Projectile_bomb_blast::Projectile_bomb_blast(string texture_file, sf::Vector2f position,
      sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd)
      : Projectile(texture_file, position, size, hit_rad, dir, mov_spd, damage_init, rotation_offset_init){}

//copy-constructor, sets frame_to_die
Projectile_bomb_blast::Projectile_bomb_blast(Projectile_bomb_blast const& other)
    : Projectile(other)
{
  frame_to_die = Game::get_frame() + frames_to_live;
}

//clone and adds to vector projectiles
void Projectile_bomb_blast::clone(sf::Vector2f dir, sf::Vector2f pos)
{
  Projectile_bomb_blast *p = new Projectile_bomb_blast{*this};
  p->direction = dir;
  p->setPosition(pos);
  projectiles.push_back(p);
}

//Returnes false, will not be deleted when collided
bool Projectile_bomb_blast::collision()
{
    return false;
}
