#ifndef TOWER_H
#define TOWER_H
#include <string>
#include "Entity.h"
#include <SFML/System/Vector2.hpp>



class Tower : public Entity
{
  public:
    Tower(std::string texture_file, sf::Vector2f position,
          sf::Vector2f siz, float hit_rad,
          sf::Vector2f dir, float mov_spd/*, int arg_level*/):
          Entity(texture_file,
                 position, 
                 siz,
                 hit_rad,
                 dir, 
                 mov_spd) /*,
          level{arg_level}*/{}

    ~Tower() noexcept = default;

    void collision(Entity* object) override;
    virtual void shoot()=0;
    void make_projectile(sf::Vector2f velocity);

    static std::vector<Tower*> static_towers;
  protected:
    std::vector<Entity *> shootable_enemies;
    int frame_last_shot;
    int fire_period;
    float detection_radius;
    Projectile *projectile;
};

class Tower_basic : public Tower
{
public:
  Tower_basic() = default;
  ~Tower_basic() noexcept = default;

  void shoot() override;
  Entity *select_target();
  sf::Vector2f aim();

  static Sprite sprite_init;
  static int frames_to_wait_init;
  static Projectile *projectile_init;
  static int fire_period_init;
  static Sprite shop_sprite_init; // inte konst, måste kunna ändras i game
  static int cost_init; //           -------||----------------------------
};

class Tower_ring : public Tower
{
public:
  Tower_ring() = default;
  ~Tower_ring() noexcept = default;

  void shoot() override;

  static Sprite sprite_init;
  static int frames_to_wait_init;
  static Projectile *projectile_init;
  static Sprite shop_sprite_init; // samma här som för basic
  static int cost_init; 
protected:
  int num_of_projectile;
};


#endif
