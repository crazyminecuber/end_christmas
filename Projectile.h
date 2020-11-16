#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include <string>

class Projectile : public Entity
{
public:
  Projectile(std::string texture_file, sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd, int arg_life):
        Entity(std::string texture_file, sf::Vector2f position, sf::Vector2f siz,
        float hit_rad, sf::Vector2f dir, float mov_spd)
        {}
  ~Projectile() noexcept = default;

  void update_position();
  static std::vector<Projectile*> projectiles;

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

  void collision(Entity* object) override;
  static int frames_to_live();
  static int damage_init();

};

class Projectile_bomb : public Projectile
{
public:
  Projectile_bomb() : Projectile()
  {}
  ~Projectile_bomb() noexcept = default;

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

  void collision(Entity* object) override;
  static int frames_to_live();
  static int damage_init();

};
#endif
