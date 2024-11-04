#include <iostream>
#include <thread>
#include <windows.h>

// Maxim Stanchik

using namespace std;

CRITICAL_SECTION criticalSection; // объявление переменной критической секции

DWORD WINAPI threadFunction(LPVOID lpParam) { // функция, которую будет выполнять каждый поток. функция принимает указатель на данные потока
    string threadName = *(string*)lpParam; // преобразауем указатель в строку, чтобы использовать имя потока
    delete (string*)lpParam; // освобождаем память, выделенную под имя потока

    for (int i = 1; i <= 90; i++) { // цикл выполняется 90 итераций 
        if (i == 30) { // когда i достигает 30, поток входит в критическую секцию, что блокирует другие потоки от выполнения данного кода
            EnterCriticalSection(&criticalSection);
        }

        cout << "Поток " << threadName << ". Итерация " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); 

        if (i == 60) {
            LeaveCriticalSection(&criticalSection); // выход из критической секции, что позволяет другим потокам продолжить свое выполнение
        }
    }

    return 0;
}

HANDLE createThread(const string& threadName) { // создание нового потока
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