#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;

// Maxim Stanchik
void OS04_02_T1() {
    DWORD processID = GetCurrentProcessId();
    DWORD threadID = GetCurrentThreadId();

    cout << "Идентификатор текущего процесса: " << processID << endl;
    cout << "Идентификатор текущего потока: " << threadID << endl;

    for (int i = 0; i < 50; i++) {
        cout << "Итерация: " << i << endl;
        Sleep(1000);
    }
};

// Maxim Stanchik
void OS04_02_T2() {
    DWORD processID = GetCurrentProcessId();
    DWORD threadID = GetCurrentThreadId();

    cout << "Идентификатор текущего процесса: " << processID << endl;
    cout << "Идентификатор текущего потока: " << threadID << endl;

    for (int i = 0; i < 125; i++) {
        cout << "Итерация: " << i << endl;
        Sleep(1000);
    }
};

// Maxim Stanchik
int main() {
    setlocale(LC_ALL, "Rus");

    DWORD processID = GetCurrentProcessId();

    cout << "Идентификатор текущего процесса: " << processID << endl;

    thread thread_T1(OS04_02_T1);
    thread thread_T2(OS04_02_T2);

    for (int i = 0; i < 100; i++) {
        cout << "Итерация: " << i << endl;

        Sleep(1000);
    }

    thread_T1.join();
    thread_T2.join();

    return 0;
};