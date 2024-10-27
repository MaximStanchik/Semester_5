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

void setSocketOptions(SOCKET sock) {
    int receiveBufferSize = 512;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&receiveBufferSize, sizeof(receiveBufferSize)) == SOCKET_ERROR) {
        throw runtime_error("setsockopt failed");
    }
}

void sendMessage(SOCKET sock, const std::string& message, sockaddr_in& serverAddr) {
    int sentBytes = sendto(sock, message.c_str(), message.length(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (sentBytes == SOCKET_ERROR) {
        throw runtime_error("sendto failed");
    }
}

void receiveResponse(SOCKET sock) {
    char buffer[500]; 
    int receivedBytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
    if (receivedBytes == SOCKET_ERROR) {
        throw runtime_error("recvfrom failed");
    }
    buffer[receivedBytes] = '\0';  
    cout << "Received response from server: " << buffer << endl;
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int main() {
    try {
        initializeWinsock();
        SOCKET clientSocket = createSocket();
        setSocketOptions(clientSocket);

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(2000);
        if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
            throw runtime_error("Invalid address");
        }

        int messageCount;
        cout << "Enter the number of messages to send: ";
        cin >> messageCount;

        for (int i = 0; i < messageCount; ++i) {
            string message = "Hello from the Client! This is message number " + to_string(i);
            sendMessage(clientSocket, message, serverAddr);
        }

        sendMessage(clientSocket, "exit", serverAddr);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        WSACleanup();
    }

    return 0;
}
