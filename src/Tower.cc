#include "Tower.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include "Game.h"
#include "Tile.h"
#include "State_machine.h"
using namespace std;
//Init static variables
std::vector<Tower*> Tower::towers{};
std::vector<Tower*> Tower::factory_towers{};

const unsigned int Tower::SORT_BY_DISTANCE{0};
const unsigned int Tower::SORT_BY_TILE{1};
const unsigned int Tower::SORT_BY_TILE_REVERSE{2};
const unsigned int Tower::SORT_BY_LIFE{3};
const unsigned int Tower::SORT_BY_REWARD{4};
const string Tower::target_method_base_string{"Selected targeting \n method: "};


/*---------------------------------------------------------------------------*/
//Functions for the class Tower

Tower::Tower(Tower const & other)
    : Entity(other),
    fire_period{other.fire_period},
    fire_angle{other.fire_angle},
    projectile{other.projectile},
    cost{other.cost}
{}

void Tower::init_circle_hit_rad()
{
    circle_hit_rad.setRadius(hitbox_radius);
    circle_hit_rad.setOrigin(circle_hit_rad.getGlobalBounds().width  / 2.f,
                             circle_hit_rad.getGlobalBounds().height / 2.f);
    circle_hit_rad.setFillColor(sf::Color(0, 0, 0, 40));
    circle_hit_rad.setOutlineColor(sf::Color::Black);
    circle_hit_rad.setOutlineThickness(2);
    circle_hit_rad.setPosition(getPosition());
}

void Tower::collision(Enemy* object, float distance)
{
    float tile_number = Tile::get_tile_by_coord(object->getPosition())->get_tile_number();
    shootable_enemies.emplace( 
      make_pair( 
        Multikey<float, 5>{ std::array<float,5>{distance, tile_number, 
                -tile_number, -static_cast<float>(object->get_damage()),
                -static_cast<float>(object->get_reward()) },
            sort_by }, 
        object ) );
}

//Creating ptojectiles
void Tower::make_projectile(sf::Vector2f dir, sf::Vector2f pos)
{
    projectile->clone(dir,pos);
}

// Change which key in shootable_enemies to order by.
void Tower::on_right_click()
{
  for ( Tower *t : Tower::towers )
  {
    t->target_method_render_frame = 0U;
  } target_method_render_frame = static_cast<unsigned int>(
        Game::get_frame() + State_machine::get_fps() * 3);
    switch (sort_by)
    {
        case SORT_BY_DISTANCE:
            sort_by = SORT_BY_TILE;
            target_method.setString(target_method_base_string + "First on map");
            break;

        case SORT_BY_TILE:
            sort_by = SORT_BY_TILE_REVERSE;
            target_method.setString(target_method_base_string + "Last on map");

            break;

        case SORT_BY_TILE_REVERSE:
            sort_by = SORT_BY_LIFE;
            target_method.setString(target_method_base_string + "Highest HP");
            break;
        
        case SORT_BY_LIFE:
            sort_by = SORT_BY_REWARD;
            target_method.setString(target_method_base_string + "Biggest reward");
            break;

        default:
            sort_by = SORT_BY_DISTANCE;
            target_method.setString(target_method_base_string + "Closest");
            break;
    }
}

void Tower::render(sf::RenderWindow &window)
{
  window.draw(*this);
  if ( target_method_render_frame && target_method_render_frame
      >= static_cast<unsigned int>(Game::get_frame()) )
  {
    if (first_render)
    {
      first_render = false;
      init_text();
    }
    window.draw(target_method);
  }
}

void Tower::init_text()
{
  target_method = sf::Text{target_method_base_string + "Closest",
                          Resource_manager::get_standard_font(),
                            40};
  target_method.setOrigin(0.f, 
    target_method.getGlobalBounds().height / 2.f);
  target_method.setPosition(getPosition().x + size.x, getPosition().y);
  target_method.setFillColor(sf::Color{0,0,0});
}

/*---------------------------------------------------------------------*/
//Functions for the class Tower_basic

Tower_basic::Tower_basic(Tower_basic const & other)
    : Tower(other)
{}

//Making tower_basic active.
Tower * Tower_basic::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_basic{*this};
    t->setPosition(position);
    t->init_circle_hit_rad();
    towers.push_back(t);
    return t;
}

//Shoot if shootable_enemies is not empty and
//if "frame since last shoot" > fire_period
void Tower_basic::shoot()
{
  if (!shootable_enemies.empty())
  {
    if (Game::get_frame() - frame_last_shot > fire_period)
    {
      pair<float, Entity *> target = select_target();
      sf::Vector2f aim_dir = aim_direction(target.first,
                                           target.second);
      make_projectile(aim_dir, getPosition());
      frame_last_shot = Game::get_frame();
      shootable_enemies.clear();
    }
  }
}

//Selecting enemy to shoot at
pair<float, Enemy*> Tower_basic::select_target()
{
  if (!shootable_enemies.empty())
  {
    target_enemy = make_pair(
        (*shootable_enemies.begin()).first.keys.at(0),
        (*shootable_enemies.begin()).second);
  }
  return target_enemy;
}

//Selecting direction for projectile
sf::Vector2f Tower_basic::aim_direction(const float & sq_distance, 
  Entity *target_enemy)
{
  sf::Vector2f aim = (target_enemy->getPosition());
  sf::Vector2f t_dir = (target_enemy->get_direction() );
  float distance_to_enemy = sqrt(sq_distance);
  float frames = distance_to_enemy / projectile->movement_speed;
  sf::Vector2f target = aim + t_dir*target_enemy->movement_speed*frames ;
  sf::Vector2f dir =  target - getPosition();
  float length {sqrt(dir.x * dir.x + dir.y * dir.y)};
  //Normalize vector
  sf::Vector2f norm_dir{dir.x / length, dir.y / length};
  return norm_dir;
}
//----------------------------------------------------------------------------
//Functions for the class Tower_ring

Tower_ring::Tower_ring(Tower_ring const & other)
    : Tower(other),
    num_of_projectile{other.num_of_projectile}
{}

//Making tower_ring active.
Tower * Tower_ring::create_active(sf::Vector2f position)
{
    Tower * t = new Tower_ring{*this};
    t->setPosition(position);
    t->init_circle_hit_rad(); // Not sure if hit_rad has any purpose for tower_rings?
    towers.push_back(t);
    return t;
}

//Function shoot in the class Tower_ring.
//Shoots in num_of_projectile number of directions.
void Tower_ring::shoot()
{
  if (Enemy::enemies.size() > 0)
  {
    if(num_projectile_shoot < num_of_projectile)
    {
        if (Game::get_frame() - frame_last_shot > fire_period)
        {
          float rad = (2 * M_PI / num_of_projectile) * num_projectile_shoot;
          sf::Vector2f dir{cos(rad), sin(rad)};
          make_projectile(dir, getPosition());
          frame_last_shot = Game::get_frame();
          ++num_projectile_shoot;
        }
    }
    else
    {
      num_projectile_shoot=0;
    }
  }
}

void Tower_ring::render(sf::RenderWindow &window)
{
  window.draw(*this);
}

void Tower_ring::on_right_click()
{
  ;
}