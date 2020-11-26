#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <ostream>

class Projectile : public Entity
{
public:
  Projectile(std::string texture_file, sf::Vector2f position, sf::Vector2f size,
        float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
        Entity(texture_file, position, size, hit_rad, dir, mov_spd),
        damage{arg_damage}{}
  ~Projectile()=default;

  Projectile(Projectile const& other); //Copy-constructor
  virtual void clone(sf::Vector2f dir, sf::Vector2f pos)=0;
  bool update_position();
  virtual bool collision()=0;
  //static
  static std::vector<Projectile*> projectiles;

protected:
  int damage{};
  int frame_to_die{};
};

class Projectile_basic : public Projectile
{
public:
  Projectile_basic(std::string texture_file, sf::Vector2f position,
       sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
       Projectile(texture_file, position, size, hit_rad, dir, mov_spd, arg_damage){}
  Projectile_basic(sf::Vector2f position, sf::Vector2f direction);
  ~Projectile_basic() = default;

  Projectile_basic(Projectile_basic const& other); //Copy-constructor
  void clone(sf::Vector2f dir, sf::Vector2f pos);
  bool collision();
  //static
  static int frames_to_live;
  static int damage_init;
  static entity_properties prop;
};

class Projectile_pierce : public Projectile
{
public:
  Projectile_pierce(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
        Projectile(texture_file, position, size, hit_rad, dir, mov_spd, arg_damage){}
  Projectile_pierce(sf::Vector2f position,sf::Vector2f direction);
  ~Projectile_pierce() = default;

  Projectile_pierce(Projectile_pierce const& other); //Copy-constructor
  void clone(sf::Vector2f dir, sf::Vector2f pos);
  bool collision();
  //static
  static int frames_to_live;
  static int damage_init;
  static int nr_pierce;
  static entity_properties prop;

protected:
  int nr_enemies_killed;
};

class Projectile_bomb_blast : public Projectile
{
public:
  Projectile_bomb_blast();
  Projectile_bomb_blast(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd);
  ~Projectile_bomb_blast()=default;

  void clone(sf::Vector2f dir, sf::Vector2f pos);
  Projectile_bomb_blast(Projectile_bomb_blast const& other); //Copy-constructor
  bool collision();
  //static
  static int frames_to_live;
  static int damage_init;
  static entity_properties prop;
};

class Projectile_bomb : public Projectile
{
public:
  Projectile_bomb(std::string texture_file, sf::Vector2f position,
                  sf::Vector2f size, float hit_rad, sf::Vector2f dir,
                  float mov_spd,int arg_damage):
        Projectile(texture_file, position, size, hit_rad, dir, mov_spd,
                   arg_damage), blast{}
  {}
  Projectile_bomb(sf::Vector2f position, sf::Vector2f direction);
  ~Projectile_bomb() = default;

  Projectile_bomb(Projectile_bomb const& other); //Copy-constructor
  void clone(sf::Vector2f dir, sf::Vector2f pos);
  bool collision();
  //static
  static int frames_to_live;
  static int damage_init;
  static entity_properties prop;

protected:
  Projectile_bomb_blast blast;
};

#endif
