#include "stdafx.h"

SOCKET  cS;

bool  GetServer(
	char* call,
	short            port,
	SOCKADDR_IN* from,
	int* flen
)
{

	SOCKADDR_IN server;
	memset(&server, 0, sizeof(server));
	char message[50];
	int lc = sizeof(server);


	int  lb = 0;
	if ((lb = recvfrom(cS, message, sizeof(message), NULL, (sockaddr*)&server, &lc)) == SOCKET_ERROR)
		throw  SetErrorMsgText("recfrom:", WSAGetLastError());

	if (GetLastError() == WSAETIMEDOUT) return false;

	*from = server;
	*flen = lc;


	return true;
}

int main(int argc, char* argv[])
{
	setlocale(0, "rus");

	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());

		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket:", WSAGetLastError());

		int optval = 1;

		if (setsockopt(cS, SOL_SOCKET, SO_BROADCAST,
			(char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw  SetErrorMsgText("opt:", WSAGetLastError());



		SOCKADDR_IN all;
		all.sin_family = AF_INET;
		all.sin_port = htons(2000);
		all.sin_addr.s_addr = INADDR_BROADCAST;
		char buf[] = "Hello";

		if ((sendto(cS, buf, sizeof(buf), NULL,
			(sockaddr*)&all, sizeof(all))) == SOCKET_ERROR)
			throw  SetErrorMsgText("sendto:", WSAGetLastError());

		SOCKADDR_IN server;

		int lc = sizeof(server);

		GetServer((char*)"Hello", 2000, &server, &lc);

		cout << "\nServer param: " << endl;
		cout << "port: " << htons(server.sin_port) << endl;
		cout << "adress: " << inet_ntoa(server.sin_addr) << endl;


		if (closesocket(cS) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());


		system("pause");
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}
	return 0;
}
