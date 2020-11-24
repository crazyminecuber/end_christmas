#ifndef TOWER_H
#define TOWER_H
#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"



class Tower : public Entity
{
  public:
    Tower(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int arg_level, int _cost)
    :Entity(texture_file, position,
        size, hit_rad,
        dir, mov_spd),
        level{arg_level}, cost{_cost}{}

    void collision(Entity* object);
    virtual void shoot()=0;
    void make_projectile(sf::Vector2f direction);

    static std::vector<Tower*> static_towers;
    static float detection_radius_init;
    static int fire_period_init;

  protected:
    std::vector<Entity*> shootable_enemies;
    Entity* target_enemy;
    int frame_last_shot;
    int fire_period;
    int fire_angel;

    float detection_radius;
    int level;
    Projectile *projectile;
  public:
    int cost{};
};


class Tower_basic : public Tower
{
public:
  Tower_basic(std::string texture_file, sf::Vector2f position,
      sf::Vector2f size, float hit_rad,
      sf::Vector2f dir, float mov_spd,
      int arg_level, int cost)
  : Tower(texture_file, position,
      size, hit_rad,
      dir, mov_spd, arg_level, cost){}

  ~Tower_basic();

  void shoot() override;
  Entity * select_target();
  sf::Vector2f aim();

  static Sprite sprite_init;
  static int frames_to_wait_init;
  static Projectile *projectile_init;
  static int fire_period_init;
  static Sprite shop_sprite_init;
  static int cost_init;
};

class Tower_ring : public Tower
{
public:
  Tower_ring(std::string texture_file, sf::Vector2f position,
      sf::Vector2f size, float hit_rad,
      sf::Vector2f dir, float mov_spd,
      int arg_level, int cost)
  : Tower(texture_file, position,
      size, hit_rad,
      dir, mov_spd, arg_level, cost){}
  ~Tower_ring();

  void shoot() override;

  static Sprite sprite_init;
  static int frames_to_wait_init;
  static Projectile *projectile_init;
  static Sprite shop_sprite_init;
  static int cost_init;
protected:
  int num_of_projectile;
};


#endif
