#include <iostream>
#include <thread>
#include <windows.h>

// Maxim Stanchik

using namespace std;

CRITICAL_SECTION criticalSection;

DWORD WINAPI threadFunction(LPVOID lpParam) {
    string threadName = *(string*)lpParam; 
    delete (string*)lpParam; 

    for (int i = 1; i <= 90; i++) {
        if (i == 30) {
            EnterCriticalSection(&criticalSection);
        }

        cout << "Поток " << threadName << ". Итерация " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); 

        if (i == 60) {
            LeaveCriticalSection(&criticalSection);
        }
    }

    return 0;
}

HANDLE createThread(const string& threadName) {
    return CreateThread(nullptr, 0, threadFunction, (LPVOID)new string(threadName), 0, nullptr);
}

int main() {
    setlocale(LC_ALL, "Rus");

    InitializeCriticalSection(&criticalSection); 

    const int size = 2;
    HANDLE threads[size];

    threads[0] = createThread("A");
    threads[1] = createThread("B");

    WaitForMultipleObjects(size, threads, TRUE, INFINITE);

    cout << "Освобождение ресурсов..." << endl;
    for (int i = 0; i < size; i++) {
        CloseHandle(threads[i]);
    }

    DeleteCriticalSection(&criticalSection); 

    cout << "Все потоки завершены" << endl;
    return 0;
}