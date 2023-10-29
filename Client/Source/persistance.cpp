//
// Created by kibkib on 22.10.2023.
//
#include "persistance.h"


bool AddToStartupRegistry(const std::string& programName) {

    const std::string keyPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hKey;
    TCHAR szPath[MAX_PATH];
    DWORD pathSize = GetModuleFileName(NULL, szPath, MAX_PATH);

    if (RegOpenKeyEx(HKEY_CURRENT_USER, keyPath.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        if (RegSetValueEx(hKey, programName.c_str(), 0, REG_SZ, (LPBYTE)szPath, (pathSize + 1) * sizeof(TCHAR)) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return true;
        }
        RegCloseKey(hKey);
    }

    return false;
}