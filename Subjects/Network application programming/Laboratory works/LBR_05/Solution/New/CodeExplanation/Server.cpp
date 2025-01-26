#include "stdafx.h"

int countServers = 0;// Счетчик серверов с одинаковым названием

bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen); // Функция для получения запроса от клиента
bool PutAnswerToClient(char* name, short port, struct sockaddr* to, int* lto); // Функция для отправки ответа клиенту
void GetServer(char* call, short port, struct sockaddr* from, int* flen); // Функция для получения информации о сервере

int main() {
	setlocale(LC_ALL, "Rus");

	SOCKET serverSocket;// Переменная для сокета сервера
	WSADATA winsockStateStr; // Структура для хранения информации о состоянии Winsock
	SOCKADDR_IN clientAdressStr; // Структура для хранения адреса клиента

	int clientAdressStrSize = sizeof(clientAdressStr); // Размер структуры адреса клиента
	char name[] = "Hello"; // Сообщение, которое сервер будет отправлять
	char hostname[32]; // Массив для хранения имени хоста

	try {
		// Инициализация Winsock
		if (WSAStartup(MAKEWORD(2, 0), &winsockStateStr) != 0) {
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		}
		cout << "Checking..." << endl;

		// Создание сокета для UDP
		if ((serverSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
			throw SetErrorMsgText("Socket: ", WSAGetLastError()); // Генерация исключения в случае ошибки
		}

		// Настройка структуры адреса сервера
		SOCKADDR_IN server;
		server.sin_family = AF_INET; // Использование IPv4
		server.sin_port = htons(2000); // Установка порта (2000)
		server.sin_addr.s_addr = INADDR_ANY; // Прием соединений на всех интерфейсах

		// Привязка сокета к адресу
		if (bind(serverSocket, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR) {
			throw SetErrorMsgText("bind", WSAGetLastError()); // Генерация исключения в случае ошибки
		}

		// Настройка структуры адреса клиента
		SOCKADDR_IN client;
		int clientSize = sizeof(client); // Размер структуры адреса клиента

		// Получение имени хоста
		if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
			throw SetErrorMsgText("Gethostname: ", WSAGetLastError()); // Генерация исключения в случае ошибки
		}
		cout << "Server name: " << hostname << endl;

		// Основной цикл обработки запросов от клиентов
		while (true) {
			// Ожидание запроса от клиента
			if (GetRequestFromClient(name, serverSocket, (SOCKADDR*)&client, &clientSize)) {
				cout << endl;
				cout << "Client socket: " << endl; // Вывод информации о клиенте
				cout << "IP: " << inet_ntoa(client.sin_addr) << endl; // IP-адрес клиента
				cout << "Port: " << htons(client.sin_port) << endl; // Порт клиента
				cout << "Hostname: " << gethostbyaddr((char*)&client.sin_addr, sizeof(client.sin_addr), AF_INET)->h_name << endl << endl; // Имя хоста клиента
				cout << endl;
				// Отправка ответа клиенту
				if (PutAnswerToClient(name, serverSocket, (SOCKADDR*)&client, &clientSize)) {
					cout << "Success!" << endl;
				}
			}
			else {
				cout << "Wrong call name!" << endl;
			}
		}

		// Закрытие сокета
		if (closesocket(serverSocket) == SOCKET_ERROR) {
			throw  SetErrorMsgText("Closesocket: ", WSAGetLastError());
		}

		// Очистка Winsock
		if (WSACleanup() == SOCKET_ERROR) {
			throw  SetErrorMsgText("Cleanup: ", WSAGetLastError());
		}

	}
	catch (string errorMsgText) {
		cout << "WSAGetLastError: " << errorMsgText << endl;
	}
	return 0;
}

// Функция для получения запроса от клиента
bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen)
{
	char buf[50] = ""; // Буфер для хранения данных
	int lenght; // Длина полученных данных
	cout << "\nServer " << name << " is wating..." << endl; // Сообщение о том, что сервер ждет запрос

	while (true)
	{
		// Получение данных от клиента
		if (lenght = recvfrom(port, buf, sizeof(buf), NULL, from, flen) == SOCKET_ERROR)
		{
			cout << "Error:" << endl; // Обработка ошибки
			if (WSAGetLastError() == WSAETIMEDOUT) {
				return false; // Если истекло время ожидания, возвращаем false
			}
				
			else {
				throw SetErrorMsgText("Recvfrom: ", WSAGetLastError()); // Генерация исключения в случае ошибки
			}
		}
		return strcmp(buf, name) == 0; // Возвращает true, если полученное сообщение совпадает с именем сервера
	}
}

// Функция для отправки ответа клиенту
bool PutAnswerToClient(char* name, short port, struct sockaddr* to, int* lto)
{
	return sendto(port, name, strlen(name) + 1, NULL, to, *lto); // Отправка данных клиенту
}

// Функция для получения информации о сервере
void GetServer(char* call, short port, struct sockaddr* from, int* flen)
{
	SOCKET cC; // Переменная для клиентского сокета
	SOCKADDR_IN all; // Структура для хранения адреса

	int timeout = 2000; // Время ожидания
	int optval = 1; // Значение опции

	char buf[50]; // Буфер для хранения данных

	try
	{
		// Создание клиентского сокета
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
			throw  SetErrorMsgText("socket:", WSAGetLastError()); // Генерация исключения в случае ошибки
		}

		// Настройка опции для широковещательной рассылки
		if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR) {
			throw  SetErrorMsgText("setsocketopt:", WSAGetLastError());
		}

		// Настройка времени ожидания для получения данных	
		if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int)) == SOCKET_ERROR) {
			throw  SetErrorMsgText("setsocketopt:", WSAGetLastError());
		}
		
		// Настройка структуры адреса для широковещательной рассылки
		all.sin_family = AF_INET; // Использование IPv4
		all.sin_port = htons(port); // Установка порта
		all.sin_addr.s_addr = INADDR_BROADCAST; // Широковещательный адрес

		// Отправка сообщения на широковещательный адрес
		if (sendto(cC, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all)) == SOCKET_ERROR) {
			throw SetErrorMsgText("sendto:", WSAGetLastError()); // Генерация исключения в случае ошибки
		}
			
		// Получение ответа от сервера
		if (recvfrom(cC, buf, sizeof(buf), NULL, from, flen) == SOCKET_ERROR) {
			throw SetErrorMsgText("recvfrom:", WSAGetLastError()); // Генерация исключения в случае ошибки
		}

		// Проверка совпадения полученного вызова с отправленным
		if (strcmp(call, buf) == 0) {
			countServers++; // Увеличение счетчика серверов
			cout << "There's a server with the same callsign!" << endl; // Сообщение о конфликте
			cout << "Count:" << countServers << endl; // Вывод количества конфликтующих серверов
			cout << "IP: " << inet_ntoa(((SOCKADDR_IN*)from)->sin_addr) << endl; // Вывод IP-адреса
			cout << "Port: " << ntohs(((struct sockaddr_in*)from)->sin_port) << endl; // Вывод порта
			cin.get(); // Ожидание ввода
			exit(0); // Завершение программы
		}
	}
	catch (string errorMsgText) {
		// Обработка ошибок
		if (WSAGetLastError() == WSAETIMEDOUT) {
			cout << "Number of servers with the same callsign: " << countServers << endl; // Вывод количества серверов
			if (closesocket(cC) == SOCKET_ERROR) throw SetErrorMsgText("closesocket: ", WSAGetLastError()); // Закрытие сокета
		}
		else {
			throw SetErrorMsgText("GetServer:", WSAGetLastError()); // Генерация исключения в случае ошибки
		}
	}
}



//Winsock -- это техническая спецификация, которая определяет, как сетевое программное обеспечение Windows будет получать доступ к сетевым сервисам, в том числе TCP/IP.


//int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
//wVersionRequested -- желаемая версия Winsock, которую приложение хочет использовать. Обычно задается с помощью макроса MAKEWORD, например MAKEWORD(2, 2) для версии 2.2.
// lpWSAData -- указатель на структуру WSADATA, в которую будет записана информация о версии Winsock, которая была загружена. Эта структура содержит информацию о версии, поддерживаемых протоколах и других параметрах.