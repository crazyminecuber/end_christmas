//TODO sätta destruktorer till default??
#ifndef TOWER_H
#define TOWER_H
#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "Projectile.h"




struct Tower_properties
{
  Projectile* projectile_init;
  int cost_init{};
  int fire_period_init{};
};


class Tower : public Entity
{
  public:
    Tower(std::string texture_file, sf::Vector2f position,
        sf::Vector2f size, float hit_rad,
        sf::Vector2f dir, float mov_spd,
        int _cost, Projectile*  proj)
    :Entity(texture_file, position,
        size, hit_rad,
        dir, mov_spd),
        projectile{proj},
        cost{_cost}{}
    Tower(Tower const & other);
    ~Tower() = default;
    void collision(Entity* object);
    virtual void shoot()=0;
    virtual void create_active(sf::Vector2f position) = 0;
    void make_projectile(sf::Vector2f dir, sf::Vector2f pos);


    static std::vector<Tower*> static_towers;
    static std::vector<Entity*> shootable_enemies; // Static??!? och varför Entity och inte Enemy?


  protected:
    Entity* target_enemy;
    int frame_last_shot{0};
    int fire_period;
    int fire_angle;

    Projectile* projectile; // Borde inte det vara så att tower bör äga sin passiva projektil? Så varför inte ta bort pekaren?
  public:
    int cost{};
};


class Tower_basic : public Tower
{
public:
  Tower_basic(std::string texture_file, sf::Vector2f position,
      sf::Vector2f size, float hit_rad,
      sf::Vector2f dir, float mov_spd,
      int cost, Projectile* proj)
  : Tower(texture_file, position,
      size, hit_rad,
      dir, mov_spd, cost, proj){}

  Tower_basic(): Tower(entity_prop.texture_file, sf::Vector2f{0,0},
          entity_prop.size, entity_prop.hit_rad, entity_prop.dir,
          entity_prop.mov_spd, tower_prop.cost_init, tower_prop.projectile_init)
  {}
  Tower_basic(Tower_basic const & other);
  ~Tower_basic()=default;

  void shoot() override;
  void create_active(sf::Vector2f position) override;
  Entity * select_target();
  //void rotate_to_target(Entity * target_enemy);
  sf::Vector2f aim_direction(Entity * target_enemy);
  static Tower_properties tower_prop;
  static entity_properties entity_prop;
};

class Tower_ring : public Tower
{
public:
  Tower_ring(std::string texture_file, sf::Vector2f position,
      sf::Vector2f size, float hit_rad,
      sf::Vector2f dir, float mov_spd,
      int cost, int num_proj, Projectile* proj)
  : Tower(texture_file, position,
      size, hit_rad,
      dir, mov_spd, cost, proj), num_of_projectile{num_proj}{}

  Tower_ring(): Tower(entity_prop.texture_file, sf::Vector2f{0,0},
          entity_prop.size, entity_prop.hit_rad, entity_prop.dir,
          entity_prop.mov_spd, tower_prop.cost_init, tower_prop.projectile_init),
          num_of_projectile{num_projectile_init}
  {}
  Tower_ring(Tower_ring const & other);
  ~Tower_ring() = default;

  void shoot() override;
  static Tower_properties tower_prop;
  void create_active(sf::Vector2f postion) override;
  static entity_properties entity_prop;
  static int num_projectile_init;

protected:
  int num_of_projectile;
  int num_projectile_shoot{0};
};


#endif
