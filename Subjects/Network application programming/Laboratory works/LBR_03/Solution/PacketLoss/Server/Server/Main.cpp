#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <cstdlib>  
#include <ctime>    

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void initializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw runtime_error("WSAStartup failed");
    }
}

SOCKET createSocket() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        throw runtime_error("Socket creation failed");
    }
    return sock;
}

void setSocketOptions(SOCKET sock) {
    int receiveBufferSize = 512;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&receiveBufferSize, sizeof(receiveBufferSize)) == SOCKET_ERROR) {
        throw runtime_error("setsockopt failed");
    }
}

void bindSocket(SOCKET sock, int port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        throw runtime_error("Bind failed");
    }
}

void handleMessages(SOCKET sock) {
    char buffer[500];  
    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);

    while (true) {
        int receivedBytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &addrLen);
        if (receivedBytes == SOCKET_ERROR) {
            cerr << "recvfrom failed: " << WSAGetLastError() << endl;
            continue;
        }
        buffer[receivedBytes] = '\0';
        cout << "Received message: " << buffer << endl;

        if (strcmp(buffer, "exit") == 0) {
            cout << "Received exit command, stopping server." << endl;
            break;
        }
    }
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int main() {
    try {
        initializeWinsock();
        SOCKET serverSocket = createSocket();
        setSocketOptions(serverSocket);
        bindSocket(serverSocket, 2000);
        cout << "Server is running on port 2000..." << endl;
        handleMessages(serverSocket);
        cleanup(serverSocket);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        WSACleanup();
    }

    return 0;
}
