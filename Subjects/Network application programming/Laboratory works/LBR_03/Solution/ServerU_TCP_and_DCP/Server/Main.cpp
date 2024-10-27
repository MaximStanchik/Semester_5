#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void initializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw runtime_error("WSAStartup failed");
    }
}

SOCKET createUdpSocket() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        throw runtime_error("UDP Socket creation failed");
    }
    return sock;
}

SOCKET createTcpSocket() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        throw runtime_error("TCP Socket creation failed");
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
void handleUdpMessages(SOCKET sock) {
    char buffer[1024];
    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    srand(time(0));

    while (true) {
        int receivedBytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &addrLen);
        if (receivedBytes == SOCKET_ERROR) {
            cerr << "UDP recvfrom failed: " << WSAGetLastError() << endl;
            continue;
        }
        buffer[receivedBytes] = '\0';
        cout << "UDP: Received message: " << buffer << endl;

        if (rand() % 100 < 30) {
            cout << "UDP: Simulated packet loss. Dropping this packet." << endl;
            continue;
        }

        Sleep(100); 
        if (strcmp(buffer, "exit") == 0) {
            cout << "UDP: Received exit command, but server will continue running." << endl;
            continue;
        }

        sendto(sock, buffer, receivedBytes, 0, (sockaddr*)&clientAddr, addrLen);
    }
}

void handleTcpConnections(SOCKET tcpSocket) {
    listen(tcpSocket, SOMAXCONN);

    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[1024];

    while (true) {
        SOCKET clientSocket = accept(tcpSocket, (sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "TCP accept failed: " << WSAGetLastError() << endl;
            continue;
        }

        int receivedBytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (receivedBytes == SOCKET_ERROR) {
            cerr << "TCP recv failed: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            continue;
        }
        buffer[receivedBytes] = '\0';
        cout << "TCP: Received message: " << buffer << endl;

        if (strcmp(buffer, "exit") == 0) {
            cout << "TCP: Received exit command, closing connection." << endl;
            closesocket(clientSocket);
            continue;
        }

        send(clientSocket, buffer, receivedBytes, 0);
        closesocket(clientSocket);
    }
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int main() {
    try {
        initializeWinsock();

        SOCKET udpSocket = createUdpSocket();
        setSocketOptions(udpSocket);
        bindSocket(udpSocket, 2000);
        cout << "UDP server is running on port 2000..." << endl;

        SOCKET tcpSocket = createTcpSocket();
        bindSocket(tcpSocket, 2000);
        cout << "TCP server is running on port 2000..." << endl;

        thread udpThread(handleUdpMessages, udpSocket);
        thread tcpThread(handleTcpConnections, tcpSocket);

        udpThread.join();
        tcpThread.join();

        cleanup(udpSocket);
        cleanup(tcpSocket);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        WSACleanup();
    }
    return 0;
}
