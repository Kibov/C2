//
// Created by kibkib on 28.09.2023.
//

#include "systeminfo.h"


std::string systeminfo::getUsername() {

    char name[256];
    DWORD size = sizeof(name);

    if(GetUserNameA(name,&size)){
        return name;
    }
    else{
        return "";
    }

}

std::string systeminfo::getHostname() {
    char name[256];
    DWORD size = sizeof(name);

    if(GetComputerNameA(name,&size)){
        return name;
    }
    else{
        return "";
    }
}
