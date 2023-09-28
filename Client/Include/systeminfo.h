//
// Created by kibkib on 28.09.2023.
//

#ifndef FERNFLOWER_SYSTEMINFO_H
#define FERNFLOWER_SYSTEMINFO_H
#include <string>
#include <windows.h>
#include <winbase.h>

class systeminfo {
public:
    std::string getHostname();
    std::string getUsername();

};


#endif //FERNFLOWER_SYSTEMINFO_H
