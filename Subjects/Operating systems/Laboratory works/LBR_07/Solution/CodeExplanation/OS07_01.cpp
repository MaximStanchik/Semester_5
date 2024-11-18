#include <iostream> 
#include <iomanip> // подключение библиотеки для манипуляций с форматированием
#include <ctime> // подключение библиотеки для работы с временем и датами

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	time_t mytime = time(NULL); // получение текущего времени в формате time_t
	struct tm now; // создание структуры tm для хранения временной информации

	localtime_s(&now, &mytime); // преобразование time_t в локальное время и заполнение структуры now

	cout << "Текущая локальная дата и время: " << endl;
	cout << "Дата: " << now.tm_mday << "." << (now.tm_mon + 1) << "." << (now.tm_year + 1900) << endl;
	cout << "Время: " << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << endl;
	return 0;
}
