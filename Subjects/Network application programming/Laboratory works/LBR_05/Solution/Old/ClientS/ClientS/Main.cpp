#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "Winsock2.h"  
#pragma comment(lib, "WS2_32.lib")

using namespace std;

bool GetServerByName(char* name, char* call, sockaddr* from, int* flen);

SOCKET sock;

int main() {
    setlocale(LC_ALL, "Rus");
    WSADATA wsaData;
    SOCKADDR_IN from;
    char name[] = "DESKTOP-02MG5EP"; 
    char call[] = "Hello"; 
    memset(&from, 0, sizeof(from));
    int lfrom = sizeof(from);

    try {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMsgText("Startup: ", WSAGetLastError());

        cout << "CLIENT" << endl;

        if ((sock = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
            throw SetErrorMsgText("socket: ", WSAGetLastError());
        }

        if (GetServerByName(name, call, (sockaddr*)&from, &lfrom)) {
            cout << "Connected server: " << endl;
            cout << "IP: " << inet_ntoa(from.sin_addr) << endl;
            cout << "Port: " << htons(from.sin_port) << endl;
        }

        if (closesocket(sock) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket: ", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
    }
    catch (string errorMsgText) {
        cout << "WSAGetLastError: " << errorMsgText << endl;
    }

    return 0;
}

bool GetServerByName(char* name, char* call, sockaddr* from, int* flen) {
    struct hostent* host = gethostbyname(name);
    if (host == nullptr) {
        throw SetErrorMsgText("gethostbyname: ", WSAGetLastError());
    }

    SOCKADDR_IN* serverAddr = (SOCKADDR_IN*)from;
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(3000);
    memcpy(&serverAddr->sin_addr, host->h_addr_list[0], host->h_length);

    cout << "Отправка сообщения: " << call << " на " << inet_ntoa(serverAddr->sin_addr) << ":" << ntohs(serverAddr->sin_port) << endl;

    int lbuf;
    if ((lbuf = sendto(sock, call, strlen(call) + 1, NULL, (sockaddr*)serverAddr, sizeof(*serverAddr))) == SOCKET_ERROR) {
        cout << "Отправка не удалась, код ошибки: " << WSAGetLastError() << endl;
        return false;
    }
    else {
        cout << "Отправлено байт: " << lbuf << endl;
    }

    char ibuf[50];
    if ((lbuf = recvfrom(sock, ibuf, sizeof(ibuf), NULL, from, flen)) == SOCKET_ERROR) {
        if (WSAGetLastError() == WSAETIMEDOUT) {
            cout << "Время ожидания истекло." << endl;
            return false;
        }
        else {
            cout << "Ошибка при получении ответа, код ошибки: " << WSAGetLastError() << endl;
            return false;
        }
    }

    cout << "Получили сообщение от сервера: " << ibuf << endl;
    return true;
}