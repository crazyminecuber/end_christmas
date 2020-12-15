//TODO sätta destruktorer till default??
#ifndef TOWER_H
#define TOWER_H
#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp> //remove?
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"



class Tower : public Entity
{
public:
    Tower(std::string texture_file,
        sf::Vector2f size, float hit_rad,
        int _cost, Projectile * proj, int f_period)
    :Entity(texture_file, sf::Vector2f{0,0},
            size, hit_rad,
            sf::Vector2f{1,0}, 0),
            fire_period{f_period},
            projectile{proj},
            cost{_cost}
    {
        init_circle_hit_rad(); // create circle_hit_rad for factory_towers to use when placing towers
    }

    Tower(Tower const & other);
    ~Tower() = default;
    void collision(Enemy* object);
    virtual void shoot()=0;
    virtual Tower * create_active(sf::Vector2f position) = 0;
    void make_projectile(sf::Vector2f dir, sf::Vector2f pos);

    static std::vector<Tower*> towers;
    static std::vector<Tower*> factory_towers;
    std::vector<Enemy*> shootable_enemies;

    void init_circle_hit_rad();
    sf::CircleShape circle_hit_rad;
protected:

    Entity* target_enemy;
    int frame_last_shot{0};
    int fire_period;
    int fire_angle;

    Projectile * projectile; // Borde inte det vara så att tower bör äga sin passiva projektil? Så varför inte ta bort pekaren? (Abstrakt klass går ej att instansiera, bästa jag vet är att använda unique_ptr, men kräver en del jobb)

public:
    int cost{};
};


class Tower_basic : public Tower
{
public:
  Tower_basic(std::string texture_file,
      sf::Vector2f size, float hit_rad,
      int cost, Projectile * proj, int f_period)
  : Tower(texture_file, size, hit_rad, cost, proj, f_period)
  {}

  Tower_basic(Tower_basic const & other);
  ~Tower_basic()=default;

  void shoot() override;
  Tower * create_active(sf::Vector2f position) override;
  Entity * select_target();
  sf::Vector2f aim_direction(Entity * target_enemy);
};

class Tower_ring : public Tower
{
public:
  Tower_ring(std::string texture_file,
      sf::Vector2f size, float hit_rad,
      int cost, Projectile * proj, int f_period, int num_proj)
  : Tower(texture_file, size, hit_rad, cost, proj, f_period), num_of_projectile{num_proj}{}

  Tower_ring(Tower_ring const & other);
  ~Tower_ring() = default;

  void shoot() override;
  Tower * create_active(sf::Vector2f postion) override; //referens?

protected:
  int num_of_projectile;
  int num_projectile_shoot{0};
};


#endif
