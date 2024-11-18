#include <iostream>
#include <windows.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	for (int i = 0; i < 500; i++) {
		Sleep(500);
		cout << "Итерация " << i << endl;
	}
	return 0;
}