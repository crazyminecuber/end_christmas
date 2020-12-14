#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Resource_manager.h"
#include "Projectile.h"
#include "Game.h"
#include "Tile.h"

using namespace std;


TEST_CASE("Projectile_basic")
{
  //Make instance
  sf::Vector2f v1(1.0,1.0);
  sf::Vector2f v2(2.0,2.0);
  sf::Vector2f v_dir(1.0,0);
  sf::Vector2u v3(2.0,2.0);
  sf::Vector2u v4(0.5,0.5);

  //Set Properties
  Projectile_basic::prop.texture_file = "resources/textures/Santa.png";
  Projectile_basic::prop.size = v1;
  Projectile_basic::prop.hit_rad = 5;
  Projectile_basic::prop.dir = v_dir;
  Projectile_basic::prop.mov_spd = 5;
  Projectile_basic::damage_init = 2;
  Projectile_basic::frames_to_live = 5;
  Tile::side_length = 1;

  //Check Properties
  CHECK(Projectile_basic::prop.texture_file == "resources/textures/Santa.png");
  CHECK(Projectile_basic::prop.size == v1);
  CHECK(Projectile_basic::prop.hit_rad == 5);
  CHECK(Projectile_basic::prop.dir == v_dir);
  CHECK(Projectile_basic::prop.mov_spd == 5);
  CHECK(Projectile_basic::damage_init == 2);

  //Adding projectiles and clone
  Projectile* p3 = new Projectile_basic(v2,v2);
  p3 -> clone(v_dir,v1);
  Projectile* p1 = new Projectile_basic("resources/textures/Santa.png",
                  v1, v2, 5, v1, 3, 2, 0);
  Projectile::projectiles.push_back(p1);
  Projectile* p2 = new Projectile_basic("resources/textures/Santa.png",
                  v1, v2, 6, v1, 7, 9, 0);
  Projectile::projectiles.push_back(p2);

  //Checking vector projectiles and if clone works
  CHECK(Projectile::projectiles.size()==3);
  CHECK(p1->getPosition() == v1);
  CHECK(p3->getPosition() == v2);
  CHECK(Projectile::projectiles[0]->getPosition() == v1); //clone of p3
  CHECK(Projectile::projectiles[0]->movement_speed == 5 );

  //Chech update_position (and outside_screen)
  CHECK(Projectile::projectiles[0]->update_position(v3));
  CHECK(!(Projectile::projectiles[0]->update_position(v4)));
  CHECK(Projectile::projectiles[0]->getPosition() == sf::Vector2f(6.0,1.0));

}

TEST_CASE("Projectile_pierce")
{
  //Make instance
  sf::Vector2f v1(1.0,1.0);
  sf::Vector2f v2(2.0,2.0);
  sf::Vector2f v_dir(1.0,0);
  sf::Vector2u v3(2.0,2.0);
  sf::Vector2u v4(0.5,0.5);

  //Set Properties
  Projectile_pierce::prop.texture_file = "resources/textures/Snowball.png";
  Projectile_pierce::prop.size = v1;
  Projectile_pierce::prop.hit_rad = 5;
  Projectile_pierce::prop.dir = v_dir;
  Projectile_pierce::prop.mov_spd = 5;
  Projectile_pierce::damage_init = 2;
  Projectile_pierce::frames_to_live = 5;
  Tile::side_length = 1;

  //Check Properties
  CHECK(Projectile_pierce::prop.texture_file == "resources/textures/Snowball.png");
  CHECK(Projectile_pierce::prop.size == v1);
  CHECK(Projectile_pierce::prop.hit_rad == 5);
  CHECK(Projectile_pierce::prop.dir == v_dir);
  CHECK(Projectile_pierce::prop.mov_spd == 5);
  CHECK(Projectile_pierce::damage_init == 2);

  //Adding projectiles and clone
  Projectile* p3 = new Projectile_pierce(v2,v2);
  p3 -> clone(v_dir,v1);
  Projectile* p1 = new Projectile_pierce("resources/textures/icicle1.png",
                  v1, v2, 5, v1, 3, 2, 2, 0);
  Projectile::projectiles.push_back(p1);
  Projectile* p2 = new Projectile_pierce("resources/textures/icicle1.png",
                  v1, v2, 6, v1, 7, 9, 2, 0);
  Projectile::projectiles.push_back(p2);

  //Checking vector projectiles and if clone works
  CHECK(Projectile::projectiles.size()==6);
  CHECK(p1->getPosition() == v1);
  CHECK(p3->getPosition() == v2);
  CHECK(Projectile::projectiles[3]->getPosition() == v1); //clone of p3
  CHECK(Projectile::projectiles[3]->movement_speed == 5 );

  //Chech update_position (and outside_screen)
  CHECK(Projectile::projectiles[3]->update_position(v3));
  CHECK(!(Projectile::projectiles[3]->update_position(v4)));
  CHECK(Projectile::projectiles[3]->getPosition() == sf::Vector2f(6.0,1.0));
}

TEST_CASE("Projectile_bomb")
{
  //Make instance
  sf::Vector2f v1(1.0,1.0);
  sf::Vector2f v2(2.0,2.0);
  sf::Vector2f v_dir(1.0,0);
  sf::Vector2u v3(2.0,2.0);
  sf::Vector2u v4(0.5,0.5);

  //Set Properties
  Projectile_bomb::prop.texture_file = "resources/textures/Santa.png";
  Projectile_bomb::prop.size = v1;
  Projectile_bomb::prop.hit_rad = 5;
  Projectile_bomb::prop.dir = v_dir;
  Projectile_bomb::prop.mov_spd = 5;
  Projectile_bomb::damage_init = 2;
  Projectile_bomb::frames_to_live = 5;
  Tile::side_length = 1;

  //Check Properties
  CHECK(Projectile_bomb::prop.texture_file == "resources/textures/Santa.png");
  CHECK(Projectile_bomb::prop.size == v1);
  CHECK(Projectile_bomb::prop.hit_rad == 5);
  CHECK(Projectile_bomb::prop.dir == v_dir);
  CHECK(Projectile_bomb::prop.mov_spd == 5);
  CHECK(Projectile_bomb::damage_init == 2);

  //Adding projectiles and clone
  Projectile* p3 = new Projectile_bomb(v2,v2);
  p3 -> clone(v_dir,v1);
  Projectile* p1 = new Projectile_bomb("resources/textures/Santa.png",
                  v1, v2, 5, v1, 3, 2, 0 );
  Projectile::projectiles.push_back(p1);
  Projectile* p2 = new Projectile_bomb("resources/textures/Santa.png",
                  v1, v2, 6, v1, 7, 9, 0);
  Projectile::projectiles.push_back(p2);

  //Checking vector projectiles and if clone works
  CHECK(Projectile::projectiles.size()==9);
  CHECK(p1->getPosition() == v1);
  CHECK(p3->getPosition() == v2);
  CHECK(Projectile::projectiles[6]->getPosition() == v1); //clone of p3
  CHECK(Projectile::projectiles[6]->movement_speed == 5 );

  //Chech update_position (and outside_screen)
  CHECK(Projectile::projectiles[6]->update_position(v3));
  CHECK(!(Projectile::projectiles[6]->update_position(v4)));
  CHECK(Projectile::projectiles[6]->getPosition() == sf::Vector2f(6.0,1.0));
}

TEST_CASE("Projectile_bomb_blast")
{
  //Vector
  sf::Vector2f v1(1.0,1.0);
  sf::Vector2f v2(2.0,2.0);
  sf::Vector2f v_dir(1.0,0);
  sf::Vector2u v3(2.0,2.0);
  sf::Vector2u v4(0.5,0.5);

  Tile::side_length = 1;

  //Adding projectiles and Clone
  Projectile* p1 = new Projectile_bomb_blast("resources/textures/Santa.png",
                  v1, v2, 5, v1, 3);
  Projectile::projectiles.push_back(p1);
  Projectile* p2 = new Projectile_bomb_blast("resources/textures/Santa.png",
                  v1, v2, 6, v1, 7);
  Projectile::projectiles.push_back(p2);
  p1 ->clone(v_dir, v1);

  //Checking vector projectiles and if clone works
  CHECK(Projectile::projectiles.size()==12);
  CHECK(p1->getPosition() == v1);
  CHECK(Projectile::projectiles[9]->getPosition() == v1); //clone of p3
  CHECK(Projectile::projectiles[9]->movement_speed == 3 );

  //Chech update_position (and outside_screen)
  CHECK(Projectile::projectiles[9]->update_position(v3));
  CHECK(!(Projectile::projectiles[9]->update_position(v4)));
  CHECK(Projectile::projectiles[9]->getPosition() == sf::Vector2f(4.0,4.0));
}
