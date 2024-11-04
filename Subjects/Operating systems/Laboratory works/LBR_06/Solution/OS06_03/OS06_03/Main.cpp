#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE hMutex;

DWORD WINAPI ProcessFunction(LPVOID lpParam) {
    string processName = static_cast<char*>(lpParam);

    for (int i = 0; i < 90; ++i) {
        if (i == 30) {
            WaitForSingleObject(hMutex, INFINITE);
        }

        cout << processName << ": Iteration " << i + 1 << endl;
        Sleep(100);

        if (i == 60) {
            ReleaseMutex(hMutex);
        }
    }

    return 0;
}

int main() {
    hMutex = CreateMutex(NULL, FALSE, NULL);

    if (hMutex == NULL) {
        cerr << "CreateMutex error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hThreadA = CreateThread(NULL, 0, ProcessFunction, (LPVOID)"Process A", 0, NULL);
    HANDLE hThreadB = CreateThread(NULL, 0, ProcessFunction, (LPVOID)"Process B", 0, NULL);
    HANDLE hThreadMain = CreateThread(NULL, 0, ProcessFunction, (LPVOID)"Process Main", 0, NULL);

    if (hThreadA == NULL || hThreadB == NULL) {
        cerr << "CreateThread error: " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(hThreadA, INFINITE);
    WaitForSingleObject(hThreadB, INFINITE);
    WaitForSingleObject(hThreadMain, INFINITE);

    CloseHandle(hThreadA);
    CloseHandle(hThreadB);
    CloseHandle(hThreadMain);
    CloseHandle(hMutex);

    return 0;
}
