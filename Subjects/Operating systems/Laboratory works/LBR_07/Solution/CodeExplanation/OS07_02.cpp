#include <Windows.h> // Подключение библиотеки Windows для работы с функциями Windows API
#include <iostream>
#include <ctime> // Подключение библиотеки для работы с временем

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	clock_t startTimer = clock(); // запись начального времени в тиках процессора
	int counter = 0; // инициализация счетчика итераций
	bool flag5sec = true, flag10sec = true; // флаги для проверки истечения времени

	while (true)
	{
		counter++;
		if (((clock() - startTimer) / CLOCKS_PER_SEC) == 5 && flag5sec) { //clock() измеряет время процессора, а не реальное время. 
			cout << "Кол-во итераций по истечению 5 секунд: " << counter << '\n'; //clock() возвращает значение типа clock_t, которое представляет собой количество тиков процессора, 
            flag5sec = false;                                                     //прошедших с момента, когда программа была запущена.
		}
		if (((clock() - startTimer) / CLOCKS_PER_SEC) == 10 && flag10sec) {
			cout << "Кол-во итераций по истечению 10 секунд: " << counter << '\n';
			flag10sec = false;
		}
		if (((clock() - startTimer) / CLOCKS_PER_SEC) == 15) {
			cout << "Кол-во итераций по истечению 15 секунд: " << counter << '\n';
			break;
		}
	}

	return 0;
}