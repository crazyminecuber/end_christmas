#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include <string>

class Projectile : public Entity
{
public:
  Projectile(std::string texture_file, sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd):
        Entity(texture_file, position, siz, hit_rad, dir, mov_spd){}
  ~Projectile() noexcept = default;
  Projectile(Projectile const& other); //Kopieringskonstruktor

  void update_position();
  static std::vector<Projectile*> projectiles;
  // static void new_projectile_basic(std::Vector2f position);
  // static void new_projectile_pierce(std::Vector2f position);
  // static void new_projectile_bomb(std::Vector2f position);

protected:
  int damage();
  int frame_to_die();

};

class Projectile_basic : public Projectile
{
public:
  Projectile_basic() : Projectile()
  {}
  ~Projectile_basic() noexcept = default;
  Projectile_basic(Projectile_basic const& other); //Kopieringskonstruktor

  void collision(Entity* object) override;
  static int frames_to_live();
  static int damage_init();

};

class Projectile_pierce : public Projectile
{
public:
  Projectile_pierce() : Projectile()
  {}
  ~Projectile_pierce() noexcept = default;

  Projectile_pierce(Projectile_pierce const& other); //Kopieringskonstruktor
  void collision(Entity* object) override;
  static int frames_to_live();
  static int damage_init();
protected:
  int nr_pierce;

};

class Projectile_bomb : public Projectile
{
public:
  Projectile_bomb() : Projectile()
  {}
  ~Projectile_bomb() noexcept = default;

  Projectile_bomb(Projectile_bomb const& other); //Kopieringskonstruktor
  void collision(Entity* object) override;
  static int frames_to_live();
  static int damage_init();

};

class Projectile_bomb_blast : public Projectile
{
public:
  Projectile_bomb_blast() : Projectile()
  {}
  ~Projectile_bomb_blast();

  Projectile_bomb_blast(Projectile_bomb_blast const& other); //Kopieringskonstruktor
  void update_rad();
  void collision(Entity* object) override;
  static int frames_to_live();
  static int damage_init();
protected:
  int blast_rad;

};
#endif
