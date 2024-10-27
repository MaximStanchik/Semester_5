#include <iostream>
#include <tchar.h>
#include <winsock2.h> 
#include <string>
#include <ws2tcpip.h> 
#pragma comment(lib, "WS2_32.lib") 

using namespace std;

string GetErrorMsgText(int code) {
    string msgText;
    switch (code) {
    case WSAEINTR:
        msgText = "WSAEINTR: Interrupted function call.";
        break;
    case WSAEACCES:
        msgText = "WSAEACCES: Permission denied.";
        break;
    case WSASYSCALLFAILURE:
        msgText = "WSASYSCALLFAILURE: System call failure.";
        break;
    default:
        msgText = "***ERROR***: Unknown error code.";
        break;
    }
    return msgText;
}

string SetErrorMsgText(string msgText, int code) {
    return msgText + " " + GetErrorMsgText(code);
}

int main(int args, _TCHAR* argv[]) {
    SOCKET sS;
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed." << endl;
        return 1;
    }

    try {
        sS = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sS == INVALID_SOCKET) {
            throw SetErrorMsgText("socket failed:", WSAGetLastError());
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(2000);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sS, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            throw SetErrorMsgText("bind failed:", WSAGetLastError());
        }

        if (listen(sS, SOMAXCONN) == SOCKET_ERROR) {
            throw SetErrorMsgText("listen failed:", WSAGetLastError());
        }

        cout << "Server is listening on port 2000..." << endl;

        while (true) {
            SOCKET cS; 
            sockaddr_in clnt; 
            memset(&clnt, 0, sizeof(clnt));
            int lclnt = sizeof(clnt);

            if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET) {
                cout << "accept failed: " << GetErrorMsgText(WSAGetLastError()) << endl;
                continue; 
            }

            char ipStr[INET_ADDRSTRLEN]; 
            if (inet_ntop(AF_INET, &clnt.sin_addr, ipStr, sizeof(ipStr)) == nullptr) {
                throw SetErrorMsgText("inet_ntop failed:", WSAGetLastError());
            }
            cout << "Client connected!" << endl;
            cout << "Client IP: " << ipStr << endl;
            cout << "Client Port: " << ntohs(clnt.sin_port) << endl;

            clock_t start = clock();

            while (true) {
                char buffer[1024];
                int bytesReceived = recv(cS, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) {
                    cout << "Client disconnected." << endl;
                    break; 
                }
                buffer[bytesReceived] = '\0'; 
                cout << "Received message: " << buffer << endl;

                send(cS, buffer, bytesReceived, 0);
            }

            clock_t end = clock();
            double elapsedTime = double(end - start) / CLOCKS_PER_SEC;
            cout << "Time taken for message exchange: " << elapsedTime << " seconds." << endl;

            if (closesocket(cS) != 0) {
                throw SetErrorMsgText("closesocket failed:", WSAGetLastError());
            }
        }

        if (closesocket(sS) != 0) {
            throw SetErrorMsgText("closesocket failed:", WSAGetLastError());
        }

    }
    catch (string errorMsgText) {
        cout << endl << "Error: " << errorMsgText << endl;
    }

    WSACleanup();
    return 0;
}