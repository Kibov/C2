//
// Created by kibkib on 23.09.2023.
//
#include <array>
#include <memory>
#include <sstream>
#include "shell.h"

std::string shell(const std::string &cmd) {
    std::array<char, 128> buffer{};
    std::stringstream resultStream; // Use stringstream to accumulate data

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        return "FAIL";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        resultStream << buffer.data(); // Append data to the stringstream
    }

    return resultStream.str(); // Convert stringstream to string and return it
}
