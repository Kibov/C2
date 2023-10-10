//
// Created by kibkib on 28.09.2023.
//

#include "systeminfo.h"
#include "windows.h"
#include <iostream>

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

std::string systeminfo::getIntegrity() {
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hToken;
    OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);

    DWORD integrityLevel;
    DWORD bufferSize = sizeof(integrityLevel);

    GetTokenInformation(hToken, TokenIntegrityLevel, nullptr, 0, &bufferSize);

    CloseHandle(hToken);

    std::string integrity {"UNKNOWN"};

    if (integrityLevel == SECURITY_MANDATORY_LOW_RID) {
        integrity = "Below Low";
    }
    else if (integrityLevel <= SECURITY_MANDATORY_MEDIUM_RID) {
        integrity = "Medium";
    }
    else if (integrityLevel <= SECURITY_MANDATORY_HIGH_RID) {
        integrity = "High";
    }
    else if (integrityLevel <= SECURITY_MANDATORY_SYSTEM_RID) {
        integrity = "SYSTEM";
    }
    return integrity;
}
