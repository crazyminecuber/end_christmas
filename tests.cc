#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Resource_manager.h"
#include "Enemy.h"
#include "Enemy_basic.h"
#include "Enemy_boss.h"
#include "Wallet.h"
using namespace std;

TEST_CASE("Hello world")
{
    CHECK(1 + 1 == 2);
}

/*
// TODO: Lägg till test fall för:
// Att lägga till fiender i enemy-vektorn

TEST_CASE("Enemy_statics")
{
    //array
    sf::Vector2f v1(5.0,5.0);
    Enemy_boss* E_BOSS = new Enemy_boss{"resources/textures/Santa.png", v1, v1, 5.0, v1, 3, 5};
    Enemy_basic* E_BASIC = new Enemy_basic{"resources/textures/Santa.png", v1, v1, 5.0, v1, 3, 5};
    Enemy::enemies.push_back(E_BOSS);
    Enemy::enemies.push_back(E_BASIC);
    CHECK(size(Enemy::enemies) == 2);

    Enemy_basic::position_init = v1;
    Enemy_basic::prop.texture_file = "resources/textures/Santa.png";
    Enemy_basic::prop.size = v1;
    Enemy_basic::prop.hit_rad = 5;
    Enemy_basic::prop.dir = v1;
    Enemy_basic::prop.mov_spd = 3;
    Enemy_basic::life_init = 1;

    CHECK(Enemy_basic::position_init == v1);
    CHECK(Enemy_basic::prop.texture_file == "resources/textures/Santa.png");
    CHECK(Enemy_basic::prop.size == v1);
    CHECK(Enemy_basic::prop.hit_rad == 5);
    CHECK(Enemy_basic::prop.dir == v1);
    CHECK(Enemy_basic::prop.mov_spd == 3);
    CHECK(Enemy_basic::life_init == 1);

    Enemy_boss::position_init = v1;
    Enemy_boss::prop.texture_file = "resources/textures/Santa.png";
    Enemy_boss::prop.size = v1;
    Enemy_boss::prop.hit_rad = 5;
    Enemy_boss::prop.dir = v1;
    Enemy_boss::prop.mov_spd = 3;
    Enemy_boss::life_init = 2;

    CHECK(Enemy_boss::position_init == v1);
    CHECK(Enemy_boss::prop.texture_file == "resources/textures/Santa.png");
    CHECK(Enemy_boss::prop.size == v1);
    CHECK(Enemy_boss::prop.hit_rad == 5);
    CHECK(Enemy_boss::prop.dir == v1);
    CHECK(Enemy_boss::prop.mov_spd == 3);
    CHECK(Enemy_boss::life_init == 2);

    //Delete all previous enemies
    Enemy::delete_all_enemies();
}

TEST_CASE("Creating new enemies")
{
    sf::Vector2f v1(5.0,5.0);
    Enemy_basic::position_init = v1;
    Enemy_basic::prop.texture_file = "resources/textures/Santa.png";
    Enemy_basic::prop.size = v1;
    Enemy_basic::prop.hit_rad = 5;
    Enemy_basic::prop.dir = v1;
    Enemy_basic::prop.mov_spd = 3;
    Enemy_basic::life_init = 1;

    Enemy_boss::position_init = v1;
    Enemy_boss::prop.texture_file = "resources/textures/Santa.png";
    Enemy_boss::prop.size = v1;
    Enemy_boss::prop.hit_rad = 5;
    Enemy_boss::prop.dir = v1;
    Enemy_boss::prop.mov_spd = 3;
    Enemy_boss::life_init = 2;

    Enemy::new_basic();
    Enemy::new_basic();
    Enemy::new_basic(v1);
    Enemy::new_basic(v1);
    Enemy::new_basic(v1);
    Enemy::new_boss();
    Enemy::new_boss();
    Enemy::new_boss();
    Enemy::new_boss();
    Enemy::new_boss();
    CHECK(size(Enemy::enemies) == 10);
    Enemy::delete_all_enemies();
}

TEST_CASE("Resource_manager")
{
  //Check that resouce_manager doens't load same sprite more than ones
  sf::Texture test{};
  sf::Texture test2{};
  test = Resource_manager::load("resources/textures/Santa.png");
  test2 = Resource_manager::load("resources/textures/Santa.png");
  CHECK(Resource_manager::get_num_of_resources() == 1);
}

TEST_CASE("Projectile_basic")
{
  //Make instance
  sf::Vector2f v1(1.0,1.0);
  sf::Vector2f v2(2.0,2.0);
  Projectile_basic* P_BASIC = new Projectile_basic{"resources/textures/Snowball.png", v1, v2, 1.0, v1, 1, 5};
  Projectile::projectiles.push_back(P_BASIC);
  Projectile_pierce* P_PIERCE = new Projectile_pierce{"resources/textures/Snowball.png", v1, v2, 1.0, v1, 1, 5};
  Projectile::projectiles.push_back(P_PIERCE);
  CHECK(size(Projectile::projectiles) ==2);

  Projectile_basic::position = v1;
  Projectile_basic::prop.texture_file = "resources/textures/Snowball.png";
  Projectile_basic::prop.size = v1;
  Projectile_basic::prop.hit_rad = 5;
  Projectile_basic::prop.dir = v1;
  Projectile_basic::prop.mov_spd = 3;
  Projectile_basic::damage_init = 2;

  CHECK(Projectile_basic::position == v1);
  CHECK(Projectile_basic::prop.texture_file == "resources/textures/Santa.png");
  CHECK(Projectile_basic::prop.size == v1);
  CHECK(Projectile_basic::prop.hit_rad == 5);
  CHECK(Projectile_basic::prop.dir == v1);
  CHECK(Projectile_basic::prop.mov_spd == 3);
  CHECK(Projectile_basic::damage_init == 2);

}

TEST_CASE("Tower_basic")
{
  Tower_basic::position_init = v1;
  Tower_basic::prop.texture_file = "resources/textures/Santa.png";
  Tower_basic::prop.size = v1;
  Tower_basic::prop.hit_rad = 5;
  Tower_basic::prop.dir = v1;
  Tower_basic::prop.mov_spd = 3;
}
*/

void t(Wallet & w)
{

}

TEST_CASE("Wallet")
{

    Wallet w{1000};
    w.ui_callback = t;
    CHECK(w.getCash() == 1000);
    CHECK(w.take(200));
    CHECK(w.getCash() == 800);
    CHECK(!(w.take(2000)));
    w.add(91);
    CHECK(w.getCash() == 891);
}

