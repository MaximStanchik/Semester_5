#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	int i = 0;
	DWORD startTime = timeGetTime();
	for (;;) {
		if (timeGetTime() - startTime >= 3000) {
			cout << "Итерация " << i << endl;
			startTime = timeGetTime();
		}
		Sleep(100); 
		i = i + 1;
	}
	return 0;
}