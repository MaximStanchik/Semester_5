#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI ThreadZed(LPVOID lpParam) {
    for (int i = 0; i < 10; i++) {
        cout << " (Z-" << GetCurrentThreadId() << ") ";
        Sleep(1000);
    }
    cout << " Поток Z завершается " << endl;
    return 0;
}

DWORD WINAPI ThreadWithParam(LPVOID lpParam) {
    const char* name = static_cast<const char*>(lpParam);
    for (int i = 0; i < 20; i++) {
        cout << " (" << name << "-" << GetCurrentThreadId() << ") ";
        Sleep(1000);
    }
    cout << " Поток " << name << " завершается" << endl;
    return 0;
}
// Maxim Stanchik
int main() {
    setlocale(LC_ALL, "RUS");

    HANDLE t1 = CreateThread(nullptr, 0, ThreadZed, nullptr, 0, nullptr);
    HANDLE t1a = CreateThread(nullptr, 0, ThreadWithParam, (LPVOID)"Максим", 0, nullptr);
    HANDLE t1b = CreateThread(nullptr, 0, ThreadWithParam, (LPVOID)"Станчик", 0, nullptr);

    for (int i = 0; i < 5; i++) {
        cout << " (*-" << GetCurrentThreadId() << ") ";
        Sleep(1000);
    }
    cout << "Главный поток завершается" << endl;

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t1a, INFINITE);
    WaitForSingleObject(t1b, INFINITE);

    CloseHandle(t1);
    CloseHandle(t1a);
    CloseHandle(t1b);

    return 0;
}