#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable: 4996)
#include "Winsock2.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <winsock2.h> 
using namespace std;

int countServers = 0;

bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen);
bool PutAnswerToClient(char* name, short port, struct sockaddr* to, int* lto);
void GetServer(char* call, short port, struct sockaddr* from, int* flen);
void PrintHostName(); 

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SOCKET sS;
    WSADATA wsaData;
    SOCKADDR_IN client;
    int clientSize = sizeof(client);
    char name[] = "Hello";

    try {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());

        cout << "SERVER #1" << endl;

        PrintHostName();

        cout << "Checking for other servers..." << endl;
        GetServer(name, 2000, (sockaddr*)&client, &clientSize);

        if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(3000);
        serv.sin_addr.s_addr = INADDR_ANY;

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw SetErrorMsgText("bind:", WSAGetLastError());

        SOCKADDR_IN clientB;
        int clientSize = sizeof(clientB);

        while (true) {
            if (GetRequestFromClient(name, sS, (SOCKADDR*)&clientB, &clientSize)) {
                cout << endl;
                if (inet_ntoa(clientB.sin_addr) == inet_ntoa(serv.sin_addr)) {
                    cout << "Another server:" << endl;
                }
                else { // TOOD: тут что-то непонятное...
                    cout << "Client socket:" << endl;
                    struct hostent* clientHost = gethostbyaddr((const char*)&clientB.sin_addr, sizeof(clientB.sin_addr), AF_INET);
                    if (clientHost != NULL) {
                        cout << "Имя клиента: " << clientHost->h_name << endl;
                    }
                    else {
                        cout << "Не удалось получить имя клиента." << endl;
                    }
                }
                cout << "IP: " << inet_ntoa(clientB.sin_addr) << endl;
                cout << "Port: " << ntohs(clientB.sin_port) << endl;
                cout << endl;

                if (PutAnswerToClient(name, sS, (SOCKADDR*)&clientB, &clientSize)) {
                    cout << "Success!" << endl;
                }
            }
            else {
                cout << "Wrong call name!" << endl;
            }
        }

        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText) {
        std::cout << endl << "WSAGetLastError: " << errorMsgText;
    }
}

void PrintHostName() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        cout << "Не удалось получить имя хоста, код ошибки: " << WSAGetLastError() << endl;
    }
    else {
        cout << "Имя собственного компьютера: " << hostname << endl;
    }
}

bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen) {
    char buf[50] = "";
    int length;
    cout << "\nWait message..." << endl;

    while (true) {
        if ((length = recvfrom(port, buf, sizeof(buf), NULL, from, flen)) == SOCKET_ERROR) {
            cout << "Error:" << endl;
            if (WSAGetLastError() == WSAETIMEDOUT) return false;
            else throw SetErrorMsgText("Recvfrom: ", WSAGetLastError());
        }
        cout << "Получено сообщение: " << buf << endl;
        return strcmp(buf, name) == 0;
    }
}

bool PutAnswerToClient(char* name, short port, struct sockaddr* to, int* lto) {
    int lengths = strlen(name);
    return sendto(port, name, lengths + 1, NULL, to, *lto);
}

void GetServer(char* call, short port, struct sockaddr* from, int* flen) {
    SOCKET cC;
    SOCKADDR_IN all;
    int timeout = 10000;
    int optval = 1;
    char buf[50];

    try {
        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
            throw SetErrorMsgText("setsocketopt:", WSAGetLastError());

        if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int)) == SOCKET_ERROR)
            throw SetErrorMsgText("setsocketopt:", WSAGetLastError());

        all.sin_family = AF_INET;
        all.sin_port = htons(port);
        all.sin_addr.s_addr = inet_addr("172.20.10.15");

        if (sendto(cC, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all)) == SOCKET_ERROR)
            throw SetErrorMsgText("sendto:", WSAGetLastError());

        while (true) {
            if (recvfrom(cC, buf, sizeof(buf), NULL, from, flen) == SOCKET_ERROR)
                throw SetErrorMsgText("recvfrom:", WSAGetLastError());

            if (strcmp(call, buf) == 0) {
                countServers++;
                cout << "There's a server with the same callsign!" << endl;
                cout << "Count: " << countServers << endl;
                cout << "IP: " << inet_ntoa(((SOCKADDR_IN*)from)->sin_addr) << endl;
                cout << "Port: " << ntohs(((struct sockaddr_in*)from)->sin_port) << endl;
            }
        }
    }
    catch (string errorMsgText) {
        if (WSAGetLastError() == WSAETIMEDOUT) {
            cout << "Number of servers with the same callsign: " << countServers << endl;
            if (closesocket(cC) == SOCKET_ERROR)
                throw SetErrorMsgText("closesocket: ", WSAGetLastError());
        }
        else {
            throw SetErrorMsgText("GetServer:", WSAGetLastError());
        }
    }
}