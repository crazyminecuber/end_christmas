#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>

class Projectile : public Entity
{
public:
  Projectile(std::string texture_file, sf::Vector2f position, sf::Vector2f size,
        float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage, float rotation_offset):
        Entity(texture_file, position, size, hit_rad, dir, mov_spd),
        damage{arg_damage}, rotation_offset{rotation_offset}{}
  ~Projectile()=default;

  Projectile(Projectile const& other); //Copy-constructor
  virtual void clone(sf::Vector2f dir, sf::Vector2f pos)=0;
  bool update_position(sf::Vector2u const & window_size);
  virtual bool collision()=0;
  //static
  static std::vector<Projectile*> projectiles;
  int damage{};

protected:
  bool outside_screen(sf::Vector2u const & window_size);
  int frame_to_die{};
  float rotation_offset{};
};

/* ---------------------------------------------------------------------------*/
class Projectile_basic : public Projectile
{
public:
  Projectile_basic(std::string texture_file, sf::Vector2f position,
       sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd,
       int arg_damage, float rotation_offset):
       Projectile(texture_file, position, size, hit_rad, dir, mov_spd,
                  arg_damage, rotation_offset){}
  Projectile_basic(sf::Vector2f position, sf::Vector2f direction);
  ~Projectile_basic() = default;

  Projectile_basic(Projectile_basic const& other); //Copy-constructor
  void clone(sf::Vector2f dir, sf::Vector2f pos);
  bool collision();
  //static
  static int frames_to_live;
  static int damage_init;
  static float rotation_offset_init;
  static entity_properties prop;
};

/*----------------------------------------------------------------------------*/
class Projectile_pierce : public Projectile
{
public:
  Projectile_pierce(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad, sf::Vector2f dir, float mov_spd,
        int arg_damage, float rotation_offset, int nr_pier):
        Projectile(texture_file, position, size, hit_rad, dir, mov_spd,
                   arg_damage, rotation_offset), nr_pierce{nr_pier}{}
  Projectile_pierce(sf::Vector2f position,sf::Vector2f direction);
  ~Projectile_pierce() = default;

  Projectile_pierce(Projectile_pierce const& other); //Copy-constructor
  void clone(sf::Vector2f dir, sf::Vector2f pos);
  bool collision();
  void rotate_to_target(sf::Vector2f dir);
  //static
  static int frames_to_live;
  static int damage_init;
  static int nr_pierce_init;
  static float rotation_offset_init;
  static entity_properties prop;

protected:
  int nr_pierce;
  int nr_enemies_killed{0};
};

/*---------------------------------------------------------------------------*/
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
  static float rotation_offset_init;
  static entity_properties prop;
};

/*----------------------------------------------------------------------------*/
class Projectile_bomb : public Projectile
{
public:
  Projectile_bomb(std::string texture_file, sf::Vector2f position,
                  sf::Vector2f size, float hit_rad, sf::Vector2f dir,
                  float mov_spd,int arg_damage, float rotation_offset):
        Projectile(texture_file, position, size, hit_rad, dir, mov_spd,
                   arg_damage, rotation_offset), blast{}
  {}
  Projectile_bomb(sf::Vector2f position, sf::Vector2f direction);
  ~Projectile_bomb()=default;

  Projectile_bomb(Projectile_bomb const& other); //Copy-constructor
  void clone(sf::Vector2f dir, sf::Vector2f pos);
  bool collision();
  //static
  static int frames_to_live;
  static int damage_init;
  static float rotation_offset_init;
  static entity_properties prop;

protected:
  Projectile_bomb_blast blast;
};

#endif
