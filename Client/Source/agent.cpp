//
// Created by kibkib on 24.09.2023.
//

#include <iostream>
#include "agent.h"

agent::agent() {
}

std::string agent::getUsername() {
    return username;
}

std::string agent::getHostname() {
    return hostname;
}

std::string agent::getPrivilege() {
    return privilege;
}

std::string agent::getIP() {
    return listenerip;
}

unsigned int agent::getPort() {
    return listenerport;
}

unsigned int agent::getSleep() {
    return sleep;
}



