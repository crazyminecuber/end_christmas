#indef PROJECTILE_H
#DEFINE PROJECTILE_H

#include "Entity.h"
#include <string>

class Projectile : public Entity
{
public:
  Projectile() = default;
  ~Projectile() noexcept = default;

  Projectile update_position();


protected:
  static std::vector<Projectile*> projectiles;
  int damege();
  int frame_to_die();

};

class Projectile_basic : public Projectile
{
public:
  Projectile_basic() = default;
  ~Projectile_basic() noexcept = default;

  void collision(Entity const& object) override;

protected:
  static int frames_to_live();
  static int damege_int();

};

class Projectile_pierce : public Projectile
{
public:
  Projectile_pierce() = default;
  ~Projectile_pierce() noexcept = default;

  void collision(Entity* object) override;

protected:
  static int frames_to_live();
  static int damege_int();

};

class Projectile_bomb : public Projectile
{
public:
  Projectile_bomb() = default;
  ~Projectile_bomb() noexcept = default;

  void collision(Entity* object) override;

protected:
  static int frames_to_live();
  static int damege_int();

};

class Projectile_bomb_blast : public Projectile
{
public:
  Projectile_bomb_blast();
  ~Projectile_bomb_blast();

  void collision(Entity* object) override;

protected:
  static int frames_to_live();
  static int damege_int();

};
#endif
