#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

HANDLE hEvent;

void ChildProcessA() {
	WaitForSingleObject(hEvent, INFINITE);
	for (int i = 0; i < 90; ++i) {
		cout << "Process A, iteration " << i + 1 << endl;
		Sleep(100);
	}
}

void ChildProcessB() {
	WaitForSingleObject(hEvent, INFINITE);
	for (int i = 0; i < 90; ++i) {
		cout << "Process B, iteration " << i + 1 << endl;
		Sleep(100);
	}
}

int main() {
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEvent == NULL) {
		cerr << "CreateEvent failed: " << GetLastError() << endl;
		return 1;
	}

	thread processA(ChildProcessA);
	thread processB(ChildProcessB);

	for (int i = 0; i < 15; ++i) {
		cout << "Process main, iteration " << i + 1 << endl;
		Sleep(100);
	}

	SetEvent(hEvent);

	for (int i = 15; i < 90; ++i) {
		cout << "Process main, iteration " << i + 1 << endl;
		Sleep(100);
	}

	processA.join();
	processB.join();

	CloseHandle(hEvent);
	return 0;
}