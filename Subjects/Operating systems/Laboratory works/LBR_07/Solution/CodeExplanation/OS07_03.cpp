#include <Windows.h> // Подключение библиотеки Windows для работы с функциями Windows API
#include <iostream> // Подключение библиотеки для ввода и вывода
#include <ctime> // Подключение библиотеки для работы с временем

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	int i = 0; // инициализация счетчика
	DWORD startTime = timeGetTime(); // получение текущего времени в миллисекундах с момента запуска системы
	for (;;) { // бесконечный цикл
		if (timeGetTime() - startTime >= 3000) { // текущее время - время когда программу запустили >= 3 секунды
			cout << "Итерация " << i << endl;
			startTime = timeGetTime(); // обновляем время для следующей проверки
		}
		Sleep(100); 
		i = i + 1; // увеличиваем счетчик
	}
	return 0;
}