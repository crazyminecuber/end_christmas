#ifndef TOWER_H
#define TOWER_H
#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"


struct Tower_properties
{
  sf::Sprite sprite_init;
  int frames_to_wait_init;
  Projectile *projectile_init;
  sf::Sprite shop_sprite_init;
  int cost_init;
  float detection_radius_init;
  int fire_period_init;
};


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
    ~Tower()=default;

    void collision(Entity* object);
    virtual void shoot()=0;
    void make_projectile(sf::Vector2f direction);

    static std::vector<Tower*> static_towers;

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

  ~Tower_basic()=default;

  void shoot() override;
  Entity * select_target();
  sf::Vector2f aim();
  static Tower_properties tower_prop;
  static entity_properties entity_prop;
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
  ~Tower_ring()=default;

  void shoot() override;
  static Tower_properties tower_prop;
  static entity_properties entity_prop;

protected:
  int num_of_projectile;
};

#endif
