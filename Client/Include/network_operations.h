//
// Created by kibkib on 23.09.2023.
//
#include <string>

#ifndef FERNFLOWER_NETWORK_OPERATIONS_H
#define FERNFLOWER_NETWORK_OPERATIONS_H

std::string get(std::string ip, unsigned int port, std::string uri);

std::string post(std::string ip, unsigned int port, std::string uri, std::string dat);

#endif //FERNFLOWER_NETWORK_OPERATIONS_H
