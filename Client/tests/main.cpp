//
// Created by kibkib on 18.11.2023.
//
#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>
#include "catch.hpp"
#include "shell.h"
#include "xor_data.h"


TEST_CASE("Shell function executes command and returns output", "[shell]") {
    SECTION("Executing a simple command") {
        std::string result = shell("echo Hello, World!");
        REQUIRE(result == "Hello, World!\n");
    }

    SECTION("Executing a command that fails") {
        std::string result = shell("invalidcommand");
        REQUIRE(result == "");
    }

    SECTION("Executing a command with no output") {
        std::string result = shell("calc.exe");
        REQUIRE(result.empty());
    }

    SECTION("Executing a command with long output") {
        std::string result = shell("echo " + std::string(200, 'a'));
        REQUIRE(result.length() > 128);
    }
}

TEST_CASE("XOR Strings function", "[xorStrings]") {
    SECTION("Basic functionality") {
        std::string input = "Hello";
        std::string key = "World";
        std::string expected_result;
        for (size_t i = 0; i < input.length(); ++i) {
            expected_result.push_back(input[i] ^ key[i % key.length()]);
        }
        REQUIRE(xorStrings(input, key) == expected_result);
    }


    SECTION("key shorter than input") {
        std::string input = "Hello";
        std::string key = "1234";
        std::string expected_result;
        for (size_t i = 0; i < input.length(); ++i) {
            expected_result.push_back(input[i] ^ key[i % key.length()]);
        }
        REQUIRE(xorStrings(input, key) == expected_result);
    }

    SECTION("key longer than input") {
        std::string input = "Hello";
        std::string key = "12345678";
        std::string expected_result;
        for (size_t i = 0; i < input.length(); ++i) {
            expected_result.push_back(input[i] ^ key[i % key.length()]);
        }
        REQUIRE(xorStrings(input, key) == expected_result);
    }

    SECTION("1 byte key") {
        std::string input = "Hello";
        std::string key = "1";
        std::string expected_result;
        for (size_t i = 0; i < input.length(); ++i) {
            expected_result.push_back(input[i] ^ key[i]);
        }
        REQUIRE(xorStrings(input, key) == expected_result);
    }

    SECTION("Empty input") {
        std::string input = "Hello";
        std::string key = "1";
        std::string expected_result;
        for (size_t i = 0; i < input.length(); ++i) {
            expected_result.push_back(input[i] ^ key[i % key.length()]);
        }
        REQUIRE(xorStrings(input, key) == expected_result);
    }
    SECTION("Empty key string") {
        std::string input = "Hello";
        std::string Key = "";
        REQUIRE(xorStrings(input, Key) == input);
    }

}