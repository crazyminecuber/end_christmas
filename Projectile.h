#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include <string>

class Projectile : public Entity
{
public:
  Projectile(std::string texture_file, sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
        Entity(texture_file, position, siz, hit_rad, dir, mov_spd),
        damage{arg_damage}{}

  ~Projectile();

  Projectile(Projectile const& other); //Kopieringskonstruktor

  void update_position();
  static std::vector<Projectile*> projectiles;
  static entity_properties prop;

protected:
  int damage;
  int frame_to_die;

};

class Projectile_basic : public Projectile
{
public:
  Projectile_basic(std::string texture_file, sf::Vector2f position,
       sf::Vector2f siz, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
       Projectile(texture_file, position, siz, hit_rad, dir, mov_spd, arg_damage){}
  ~Projectile_basic() noexcept = default;
  Projectile_basic(Projectile_basic const& other); //Kopieringskonstruktor

  void collision(Entity* object);
  static int frames_to_live;
  static int damage_init;
  static entity_properties prop;

};

class Projectile_pierce : public Projectile
{
public:
  Projectile_pierce(std::string texture_file, sf::Vector2f position,
        sf::Vector2f siz, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
        Projectile(texture_file, position, siz, hit_rad, dir, mov_spd, arg_damage){}
  ~Projectile_pierce() noexcept = default;

  Projectile_pierce(Projectile_pierce const& other); //Kopieringskonstruktor
  void collision(Entity* object);
  static int frames_to_live;
  static int damage_init;
  static int nr_pierce;
  static entity_properties prop;
protected:
  int nr_enemies_killed;

};

class Projectile_bomb : public Projectile
{
public:
  Projectile_bomb(std::string texture_file, sf::Vector2f position,
        sf::Vector2f siz, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage):
        Projectile(texture_file, position, siz, hit_rad, dir, mov_spd, arg_damage){}
  ~Projectile_bomb() noexcept = default;

  Projectile_bomb(Projectile_bomb const& other); //Kopieringskonstruktor
  void collision(Entity* object);
  void new_bomb_blast(sf::Vector2f position);
  static int frames_to_live;
  static int damage_init;
  static entity_properties prop;

};

class Projectile_bomb_blast : public Projectile
{
public:
  Projectile_bomb_blast(std::string texture_file, sf::Vector2f position,
        sf::Vector2f siz, float hit_rad, sf::Vector2f dir, float mov_spd, int arg_damage)
        : Projectile(texture_file, position, siz, hit_rad, dir, mov_spd, arg_damage){}
  ~Projectile_bomb_blast();

  Projectile_bomb_blast(Projectile_bomb_blast const& other); //Kopieringskonstruktor
  void update_rad();
  void collision(Entity* object);
  static int frames_to_live;
  static int damage_init;
  static entity_properties prop;

};

#endif
