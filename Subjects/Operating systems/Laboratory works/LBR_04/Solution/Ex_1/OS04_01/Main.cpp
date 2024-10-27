#include <iostream>
#include <Windows.h>

using namespace std;
//Maxim Stanchik
int main() {
	setlocale(LC_ALL, "Rus");
	DWORD processID = GetCurrentProcessId();
	DWORD threadID = GetCurrentThreadId();
	cout << "Идентификатор текущего процесса (Process ID): " << processID << endl;
	cout << "Идентификатор текущего потока (Thread ID): " << threadID << endl;	
	for (int i = 0; i < 100; i++) {
		Sleep(1000);
		cout << i << endl;
	}
	return 0;
}