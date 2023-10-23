//
// Created by kibkib on 22.10.2023.
//
#include <windows.h>
#include <string>


#ifndef FERNFLOWER_PERSISTANCE_H
#define FERNFLOWER_PERSISTANCE_H
std::string getExePath();

bool AddToStartupRegistry(const std::string &value_name, const std::string &value_data);


#endif //FERNFLOWER_PERSISTANCE_H
