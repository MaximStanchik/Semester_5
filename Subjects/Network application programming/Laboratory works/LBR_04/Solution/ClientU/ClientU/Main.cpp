#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
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

void sendMessage(SOCKET sock, const string& message, sockaddr_in& serverAddr) {
    int sentBytes = sendto(sock, message.c_str(), message.length(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (sentBytes == SOCKET_ERROR) {
        throw runtime_error("sendto failed");
    }
    cout << "Сообщение отправлено: " << message << endl; 
}

void receiveResponse(SOCKET sock) {
    char buffer[1024];
    int receivedBytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
    if (receivedBytes == SOCKET_ERROR) {
        throw runtime_error("recvfrom failed");
    }
    buffer[receivedBytes] = '\0';
    cout << "Получен ответ от сервера: " << buffer << endl; 
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int main() {
    setlocale(LC_ALL, "Rus");
    try {
        initializeWinsock();
        SOCKET clientSocket = createSocket();
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(123456); 
        if (inet_pton(AF_INET, "172.20.10.15", &serverAddr.sin_addr) <= 0) {
            throw runtime_error("Invalid address");
        }

        string message = "Hello";
        sendMessage(clientSocket, message, serverAddr);
        receiveResponse(clientSocket);

        cleanup(clientSocket);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        WSACleanup();
    }
    return 0;
}