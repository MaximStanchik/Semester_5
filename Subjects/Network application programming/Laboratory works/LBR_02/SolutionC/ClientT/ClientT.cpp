#include <iostream>
#include <tchar.h>
#include <winsock2.h> 
#include <ws2tcpip.h> 
#include <string>
#include <ctime> 
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
    case WSAENETUNREACH:
        msgText = "WSAENETUNREACH: Network is unreachable.";
        break;
    case WSAECONNREFUSED:
        msgText = "WSAECONNREFUSED: Connection refused.";
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
    WSADATA wsaData;

    try {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("WSAStartup failed:", WSAGetLastError());
        }

        SOCKET sS = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sS == INVALID_SOCKET) {
            throw SetErrorMsgText("socket failed:", WSAGetLastError());
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(2000);
        if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
            throw SetErrorMsgText("inet_pton failed:", WSAGetLastError());
        }

        if (connect(sS, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw SetErrorMsgText("connect failed:", WSAGetLastError());
        }

        int messageCount;
        cout << "Enter the number of messages to send: ";
        cin >> messageCount;

        clock_t start = clock();

        for (int i = 1; i <= messageCount; ++i) {
            string message = "Hello from Client " + to_string(i);
            int bytesSent = send(sS, message.c_str(), message.length(), 0);
            if (bytesSent == SOCKET_ERROR) {
                throw SetErrorMsgText("send failed:", WSAGetLastError());
            }

            char buffer[1024];
            int bytesReceived = recv(sS, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                break; 
            }
            buffer[bytesReceived] = '\0'; 

            int msgNum = i + 1; 
            message = "Hello from Client " + to_string(msgNum);
            cout << "Received return message: " << buffer << endl;
        }

        clock_t end = clock();
        double elapsedTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Time taken for message exchange: " << elapsedTime << " seconds." << endl;

        if (closesocket(sS) != 0) {
            throw SetErrorMsgText("closesocket failed:", WSAGetLastError());
        }

        WSACleanup();
    }
    catch (string errorMsgText) {
        cout << endl << "Error: " << errorMsgText << endl;
        WSACleanup();
    }

    return 0;
}