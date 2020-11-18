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
using namespace std;

TEST_CASE("Hello world")
{
    CHECK(1 + 1 == 2);
}

// TODO: Lägg till test fall för:
// Att lägga till fiender i enemy-vektorn

TEST_CASE("Enemy_basic")
{
    // Make instance
    sf::Vector2f v1(5.0,5.0);
    sf::Vector2u v2(5,5);
    Enemy_basic E_BASIC{
        "resources/textures/Santa.png", //Texture
        v1, //Poistion
        v1, //Size
        5.0,        //Hit_rad
        v1,       //dir
        3,          //mov_spd
        5           //life
    };
}

TEST_CASE("Enemy_boss")
{
    //Make instance
    sf::Vector2f v1(5.0,5.0);
    Enemy_boss E_BOSS{"resources/textures/Santa.png",
        v1, //Poistion
        v1, //Size
        5.0,        //Hit_rad
        v1,       //dir
        3,          //mov_spd
        5           //life
    };
}

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
    CHECK(Enemy_basic::position_init == v1);
    CHECK(Enemy_basic::prop.texture_file == "resources/textures/Santa.png");
    CHECK(Enemy_basic::prop.size == v1);
    CHECK(Enemy_basic::prop.hit_rad == 5);
    CHECK(Enemy_basic::prop.dir == v1);
    CHECK(Enemy_basic::prop.mov_spd == 3);

    Enemy_basic::life_init = 1;
    CHECK(Enemy_basic::life_init == 1);

    Enemy_boss::position_init = v1;
    Enemy_boss::prop.texture_file = "resources/textures/Santa.png";
    Enemy_boss::prop.size = v1;
    Enemy_boss::prop.hit_rad = 5;
    Enemy_boss::prop.dir = v1;
    Enemy_boss::prop.mov_spd = 3;
    CHECK(Enemy_boss::position_init == v1);
    CHECK(Enemy_boss::prop.texture_file == "resources/textures/Santa.png");
    CHECK(Enemy_boss::prop.size == v1);
    CHECK(Enemy_boss::prop.hit_rad == 5);
    CHECK(Enemy_boss::prop.dir == v1);
    CHECK(Enemy_boss::prop.mov_spd == 3);

    Enemy_boss::life_init = 2;
    CHECK(Enemy_boss::life_init == 2);
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
