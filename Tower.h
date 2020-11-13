#ifndef TOWER_H
#define TOWER_H
#include <string>
#include "Entity.h"

using namespace std;

class Tower : public Entity
{
  public:
    Tower() = default;
    ~Tower() noexcept = default;

    void collision(Entity* object) override;
    virtual void shoot()=0;
    void make_projectile(Vector2f velocity);

  protected:
    static std::vector<Tower*> Tower::static_towers;
    std::vector<Entity const &> shootable_enemies;
    int frame_last_shot;
    int fire_period;
    float detection_radius;
    Projectile projectile;

};

class Tower_basic : public Tower
{
public:
  Tower_basic() = default;
  ~Tower_basic() noexcept = default;

  void shoot() override;
  Entity select_target();
  vector2<float> aim();

protected:
  static Sprite sprite_init;
  static int frames_to_wait_init;
  static Projectile projectile_init;
  static int fire_period_init;
  static Sprite shop_sprite_init const;
  static int cost_init const;
};

class Tower_ring : public Tower
{
public:
  Tower_ring() = default;
  ~Tower_ring() noexcept = default;

  void shoot() override;

protected:
  static Sprite sprite_init;
  static int frames_to_wait_init;
  static Projectile projectile_init;
  static Sprite shop_sprite_init const;
  static int cost_init const;
  int num_of_projectile;
};


#endif
