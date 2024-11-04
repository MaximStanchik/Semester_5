#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE hSemaphore;

DWORD WINAPI ProcessFunction(LPVOID lpParam) {
    string processName = static_cast<char*>(lpParam);

    for (int i = 0; i < 90; ++i) {
        if (i == 30) {
            WaitForSingleObject(hSemaphore, INFINITE);
        }

        cout << processName << ": Iteration " << i + 1 << endl;
        Sleep(100);

        if (i == 60) {
            ReleaseSemaphore(hSemaphore, 1, NULL);
        }
    }

    return 0;
}

int main() {
    hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);

    if (hSemaphore == NULL) {
        cerr << "CreateSemaphore error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hThreadA = CreateThread(NULL, 0, ProcessFunction, (LPVOID)"Process A", 0, NULL);
    HANDLE hThreadB = CreateThread(NULL, 0, ProcessFunction, (LPVOID)"Process B", 0, NULL);
    HANDLE hThreadMain = CreateThread(NULL, 0, ProcessFunction, (LPVOID)"Process Main", 0, NULL);

    if (hThreadA == NULL || hThreadB == NULL || hThreadMain == NULL) {
        cerr << "CreateThread error: " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(hThreadA, INFINITE);
    WaitForSingleObject(hThreadB, INFINITE);
    WaitForSingleObject(hThreadMain, INFINITE);

    CloseHandle(hThreadA);
    CloseHandle(hThreadB);
    CloseHandle(hThreadMain);
    CloseHandle(hSemaphore);

    return 0;
}