#ifndef TOWER_H
#define TOWER_H
#include <iostream>
#include <map>
#include <SFML/System/Vector2.hpp> //remove?
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Multikey.h"



class Tower : public Entity
{
public:
    Tower(std::string texture_file,
        sf::Vector2f size, float hit_rad,
        int _cost, std::shared_ptr<Projectile> proj, int f_period)
    :Entity(texture_file, sf::Vector2f{0,0},
            size, hit_rad,
            sf::Vector2f{1,0}, 0),
        fire_period{f_period},
        projectile{proj},
        cost{_cost}
    { 
        // create circle_hit_rad for factory_towers to use when placing towers
        init_circle_hit_rad();
    }

    Tower(Tower const & other);
    ~Tower() = default;
    void collision(Enemy* object, float distance);
    virtual void shoot()=0;
    virtual Tower * create_active(sf::Vector2f position) = 0;
    void make_projectile(sf::Vector2f dir, sf::Vector2f pos);
    virtual void on_right_click();

    static std::vector<Tower*> towers;
    static std::vector<Tower*> factory_towers;

    std::multimap<Multikey<float, 5>, Enemy*> shootable_enemies;

    void init_circle_hit_rad();
    sf::CircleShape circle_hit_rad;
    sf::Text target_method;

    virtual void render(sf::RenderWindow &window);

protected:

    std::pair<float, Enemy*> target_enemy;
    int frame_last_shot{0};
    int fire_period;
    int fire_angle;

    std::shared_ptr<Projectile> projectile; 
    static const unsigned int SORT_BY_DISTANCE;
    static const unsigned int SORT_BY_TILE;
    static const unsigned int SORT_BY_TILE_REVERSE;
    static const unsigned int SORT_BY_LIFE;
    static const unsigned int SORT_BY_REWARD;
    static const std::string target_method_base_string;
    void init_text();
    unsigned int sort_by{0};
    unsigned int target_method_render_frame{0};
    bool first_render{true};

public:
    int cost{};
};

/*---------------------------------------------------------------------------*/

class Tower_basic : public Tower
{
public:
  Tower_basic(std::string texture_file,
      sf::Vector2f size, float hit_rad,
      int cost, std::shared_ptr<Projectile> proj, int f_period)
  : Tower(texture_file, size, hit_rad, cost, proj, f_period)
  {}

  Tower_basic(Tower_basic const & other);
  ~Tower_basic() = default;

  void shoot() override;
  Tower * create_active(sf::Vector2f position) override;
  std::pair<float, Enemy *> select_target();
  sf::Vector2f aim_direction(const float & sq_distance, Entity *target_enemy);
};

/*---------------------------------------------------------------------------*/

class Tower_ring : public Tower
{
public:
  Tower_ring(std::string texture_file,
      sf::Vector2f size, float hit_rad,
      int cost, std::shared_ptr<Projectile> proj, int f_period, int num_proj)
  : Tower(texture_file, size, hit_rad, cost, proj, f_period), num_of_projectile{num_proj}{}

  Tower_ring(Tower_ring const & other);
  ~Tower_ring() = default;

  void shoot() override;
  Tower * create_active(sf::Vector2f postion) override;
  void render(sf::RenderWindow &window) override;
  void on_right_click() override;

protected:
  int num_of_projectile;
  int num_projectile_shoot{0};
};

#endif
