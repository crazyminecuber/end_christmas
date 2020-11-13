#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <string>
#include <iostream>
using namespace std;

TEST_CASE("Hello world")
{
    CHECK(1 + 1 == 2);
}
