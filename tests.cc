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

TEST_CASE("Enemy_basic")
{
    // Make instance
    sf::Vector2f v1(5.0,5.0);
    Enemy_basic E_BASIC{"resources/textures/Santa.png",
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
  Projectile_basic P_BASIC{"resources/textures/Snowball.png",
    v1, //Posistion
    v2, //Size
    1.0, //Hit_rad
    v3, //dir
    1, //move speed
    3}; //life?
}
