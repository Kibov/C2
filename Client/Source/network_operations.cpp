//
// Created by kibkib on 23.09.2023.
//
#include "network_operations.h"
#include "windows.h"
#include "winhttp.h"


std::string get(std::string ip, unsigned int port, std::string uri) {
    std::wstring sip = std::wstring(ip.begin(), ip.end());
    std::wstring suri = std::wstring(uri.begin(), uri.end());

    std::string response;

    LPSTR pszOutBuffer;

    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    BOOL bResults = FALSE;

    HINTERNET hSession = nullptr,
            hConnect = nullptr,
            hRequest = nullptr;

    hSession = WinHttpOpen(L"test",
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME,
                           WINHTTP_NO_PROXY_BYPASS,
                           0);

    if (hSession) {

        hConnect = WinHttpConnect(hSession,
                                  sip.c_str(),
                                  port,
                                  0);
    }

    if (hConnect) {

        hRequest = WinHttpOpenRequest(hConnect,
                                      L"GET", suri.c_str(),
                                      nullptr,
                                      WINHTTP_NO_REFERER,
                                      WINHTTP_DEFAULT_ACCEPT_TYPES,
                                      0);
    }

    if (hRequest) {

        bResults = WinHttpSendRequest(hRequest,
                                      WINHTTP_NO_ADDITIONAL_HEADERS,
                                      0,
                                      WINHTTP_NO_REQUEST_DATA,
                                      0,
                                      0,
                                      0);
    }

    if (bResults) {

        bResults = WinHttpReceiveResponse(hRequest, nullptr);
    }

    if (bResults) {
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {}

            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer) {
                dwSize = 0;
            } else {
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID) pszOutBuffer, dwSize, &dwDownloaded)) {}
                else {

                    response = response + std::string(pszOutBuffer);
                    delete[] pszOutBuffer;
                }
            }
        } while (dwSize > 0);
    }

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return response;
}


std::string post(std::string ip, unsigned int port, std::string uri, const std::string& dat) {
    LPSTR data = const_cast<char *>(dat.c_str());
    DWORD data_len = strlen(data);

    LPCWSTR additionalHeaders = L"Content-Type: application/x-www-form-urlencoded\r\n";
    DWORD headersLength = -1;

    std::wstring sip = std::wstring(ip.begin(), ip.end());
    std::wstring suri = std::wstring(uri.begin(), uri.end());

    std::string response;

    LPSTR pszOutBuffer;

    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    BOOL bResults = FALSE;

    HINTERNET hSession = nullptr,
            hConnect = nullptr,
            hRequest = nullptr;

    hSession = WinHttpOpen(L"test", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME,
                           WINHTTP_NO_PROXY_BYPASS,
                           0);

    if (hSession) {
        hConnect = WinHttpConnect(hSession, sip.c_str(), port, 0);
    }
    if (hConnect) {
        hRequest = WinHttpOpenRequest(hConnect, L"POST", suri.c_str(),
                                      nullptr, WINHTTP_NO_REFERER,
                                      WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    }
    if (hRequest) {
        bResults = WinHttpSendRequest(hRequest, additionalHeaders, headersLength, (LPVOID) data, data_len, data_len, 0);
    }
    if (bResults) {
        bResults = WinHttpReceiveResponse(hRequest, nullptr);
    }

    if (bResults) {

        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {}

            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer) {
                dwSize = 0;
            } else {
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID) pszOutBuffer, dwSize, &dwDownloaded)) {}
                else {
                    response = response + std::string(pszOutBuffer);
                    delete[] pszOutBuffer;
                }
            }
        } while (dwSize > 0);
    }

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return response;
}
