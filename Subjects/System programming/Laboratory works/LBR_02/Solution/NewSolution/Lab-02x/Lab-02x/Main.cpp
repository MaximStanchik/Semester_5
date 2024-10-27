#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");

	if (argc < 2) {
		cout << "���������� �������� �� ������" << endl;
		ExitProcess(1);
	}

	int iterations = atoi(argv[1]);

	if (iterations <= 0) {
		cout << "���������� �������� ������ ���� ���������� ������" << endl;
		ExitProcess(1);
	}
	
	cout << "���������� ��������: " << argv[1] << endl;

	for (int i = 0; i < iterations; i++) {
		Sleep(500);
		cout << "�������� " << i << ", PID: " << GetCurrentProcessId() << " ." << endl;
	}
	ExitProcess(0);
	return 0;
}