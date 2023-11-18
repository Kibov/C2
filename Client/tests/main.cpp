//
// Created by kibkib on 18.11.2023.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "xor_data.h"


TEST_CASE("Checking if xoring is correct"){
    REQUIRE(xorStrings("", "") == "");
    REQUIRE(xorStrings("1234", "1234") != "1234");
}