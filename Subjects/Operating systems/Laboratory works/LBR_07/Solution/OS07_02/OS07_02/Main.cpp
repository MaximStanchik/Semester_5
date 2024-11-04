#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	clock_t startTimer = clock();
	int counter = 0;
	bool flag5sec = true, flag10sec = true;

	while (true)
	{
		counter++;
		if (((clock() - startTimer) / CLOCKS_PER_SEC) == 5 && flag5sec) {
			cout << "Кол-во итераций по истечению 5 секунд: " << counter << '\n';
			flag5sec = false;
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