#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	time_t mytime = time(NULL);
	struct tm now;

	localtime_s(&now, &mytime);

	cout << "Текущая локальная дата и время: " << endl;
	cout << "Дата: " << now.tm_mday << "." << (now.tm_mon + 1) << "." << (now.tm_year + 1900) << endl;
	cout << "Время: " << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << endl;
	return 0;
}
