//#include "stdafx.h"
//
//#define NAME L"\\\\.\\mailslot\\Box"
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	cout << "Mailslot Client" << endl;
//
//	HANDLE hM; 
//	DWORD wb;
//	char obuf[50];
//	try
//	{
//		if ((hM = CreateFile(NAME,
//			GENERIC_WRITE, 
//			FILE_SHARE_READ,
//			NULL,
//			OPEN_EXISTING,
//			NULL, NULL)) == INVALID_HANDLE_VALUE)
//			throw SetErrorMsgText("CreateFileError", WSAGetLastError());
//
//		for (int i = 0; i < 1000; i++)
//		{
//			string obufstr = "Hello from Client " + to_string(i + 1);
//			strcpy_s(obuf, obufstr.c_str());
//			if (!WriteFile(hM,
//				obuf, 
//				sizeof(obuf),
//				&wb, 
//				NULL))
//				throw SetErrorMsgText("ReadFileError", WSAGetLastError());
//		}
//
//		strcpy_s(obuf,  "STOP");
//		if (!WriteFile(hM, obuf, sizeof(obuf), &wb, NULL))
//			throw SetErrorMsgText("ReadFileError", WSAGetLastError());
//		CloseHandle(hM);
//	}
//	catch(string error)
//	{ 
//		cout << endl << error << endl;
//	}
//}

//#define NAME L"\\\\*\\mailslot\\Box"
//Если при рассылке на несколько компьютеров на сервере дублируются сообщения, 
//отключите неиспользуемые адаптеры беспроводной сети в настройках Network & Internet

#include "stdafx.h"

#define SERVER_COUNT 3
#define MESSAGE_SIZE 1000

LPCWSTR serverNames[SERVER_COUNT] = {
    L"\\\\.\\mailslot\\Box1",
    L"\\\\.\\mailslot\\Box2",
    L"\\\\.\\mailslot\\Box3"
};

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Mailslot Client" << endl;

    HANDLE hM[SERVER_COUNT];
    DWORD wb;
    char obuf[MESSAGE_SIZE];

    try
    {
        for (int i = 0; i < SERVER_COUNT; i++)
        {
            hM[i] = CreateFile(serverNames[i],
                GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                NULL, NULL);

            if (hM[i] == INVALID_HANDLE_VALUE)
                throw SetErrorMsgText("CreateFileError", WSAGetLastError());
        }

        for (int i = 0; i < 1000; i++)
        {
            string obufstr = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis";
            strcpy_s(obuf, obufstr.c_str());

            size_t messageLength = strlen(obuf) + 1;
            cout << "Количество символов: " << messageLength << endl;

            for (int j = 0; j < SERVER_COUNT; j++)
            {
                if (!WriteFile(hM[j], obuf, messageLength, &wb, NULL))
                {
                    cout << "Ошибка записи на сервер " << j << ": " << WSAGetLastError() << endl;
                    throw SetErrorMsgText("WriteFileError", WSAGetLastError());
                }
            }
        }

        strcpy_s(obuf, "STOP");
        size_t stopMessageLength = strlen(obuf) + 1;

        for (int j = 0; j < SERVER_COUNT; j++)
        {
            if (!WriteFile(hM[j], obuf, stopMessageLength, &wb, NULL))
            {
                cout << "Ошибка записи на сервер " << j << ": " << WSAGetLastError() << endl;
                throw SetErrorMsgText("WriteFileError", WSAGetLastError());
            }
        }

        for (int i = 0; i < SERVER_COUNT; i++)
        {
            CloseHandle(hM[i]);
        }
    }
    catch (string error)
    {
        cout << endl << error << endl;
    }
    return 0;
}
