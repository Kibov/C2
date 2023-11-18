//
// Created by kibkib on 13.11.2023.
//


#include "xor_data.h"

std::string xorStrings(const std::string &input, const std::string &key){

    if (key.empty()) {
        return input;
    }

    std::string result;
    result.reserve(input.length());

    for (size_t i = 0; i < input.length(); ++i) {
        result.push_back(input[i] ^ key[i % key.length()]);
    }

    return result;
}

