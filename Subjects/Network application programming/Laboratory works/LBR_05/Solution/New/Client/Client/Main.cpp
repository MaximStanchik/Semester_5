#include "stdafx.h"

#pragma comment(lib, "WS2_32.lib") 
#pragma warning(disable: 4996)
#include "Winsock2.h"
#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
bool  GetServerByName(const char* name, const char* call, struct sockaddr* from, int* flen);


void main()
{
	setlocale(LC_ALL, "Rus");

	SOCKET cS;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
			throw SetErrorMsgText("Startup:", WSAGetLastError());
		}
			
		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
			throw SetErrorMsgText("socket:", WSAGetLastError());
		}
			
		sockaddr from;
		int length = sizeof(from);
		GetServerByName("DESKTOP-02MG5EP", "Hello", &from, &length);

		if (closesocket(cS) == SOCKET_ERROR) {
			throw SetErrorMsgText("closesocket:", WSAGetLastError());
		}
			

		if (WSACleanup() == SOCKET_ERROR) {
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
		}
			
	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}
}



bool GetServerByName(const char* name, const char* call, struct sockaddr* from, int* flen)
{
	SOCKET sS = socket(AF_INET, SOCK_DGRAM, NULL);

	hostent* host = gethostbyname(name);
	if (!host) {
		throw SetErrorMsgText("gethostbyname:", WSAGetLastError());
	}
		

	char* ip_addr = inet_ntoa(*(in_addr*)(host->h_addr));
	cout << "Имя хоста: " << host->h_name << endl;
	cout << "IP сервера: " << ip_addr << endl;

	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(2000);
	server.sin_addr.s_addr = inet_addr(ip_addr);
	char message[10];

	if (sendto(sS, call, strlen(call), NULL, (const sockaddr*)&server, *flen) == SOCKET_ERROR) {
		throw SetErrorMsgText("sendto:", WSAGetLastError());
	}
		
	int buf = 0;

	if ((buf = recvfrom(sS, message, sizeof(message), NULL, (sockaddr*)&server, flen)) == SOCKET_ERROR) {
		throw SetErrorMsgText("recvfrom:", WSAGetLastError());
	}

	message[buf] = 0x00;
	cout << endl;
	cout << "Message from server: " << message << endl;
	*from = *((sockaddr*)&server);
	closesocket(sS);
	return true;
} // кэш, узел куда смотрит, куда смотрит доменное имя, domain main system. как получив доменное имя, он (сервер) возвращает ip-адрес




//попробовать поставить windows 10
// попробовать скачать винсокет библиотеку на виртуалку