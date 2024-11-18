#include <iostream>
#include <thread>
#include <windows.h>

// Maxim Stanchik

using namespace std;

CRITICAL_SECTION criticalSection; // объявление критической секции для синхронизации потоков

// функция, которую будет выполнять каждый поток
DWORD WINAPI threadFunction(LPVOID lpParam) {
    string threadName = *(string*)lpParam; // получение имени потока
    delete (string*)lpParam; // освобождение памяти, выделенной под имя потока

    // цикл от 1 до 90
    for (int i = 1; i <= 90; i++) {
        // вход в критическую секцию на 30ой итерации
        if (i == 30) {
            EnterCriticalSection(&criticalSection);
        }

        // вывод информации о текущем потоке и итерации
        cout << "Поток " << threadName << ". Итерация " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); // задержка в 100 мс

        if (i == 60) {
            LeaveCriticalSection(&criticalSection); // выход из критической секции
        }
    }

    return 0;
}

// функция для создания потока
HANDLE createThread(const string& threadName) {
    return CreateThread(nullptr, 0, threadFunction, (LPVOID)new string(threadName), 0, nullptr);
}

int main() {
    setlocale(LC_ALL, "Rus");

    InitializeCriticalSection(&criticalSection); // инициализация критической секции

    const int size = 2; // кол-во потоков
    HANDLE threads[size]; // массив дескрипторов потоков

    // создание двух потоков с именами А и В
    threads[0] = createThread("A");
    threads[1] = createThread("B");

    // ожидание завершения двух потоков
    WaitForMultipleObjects(size, threads, TRUE, INFINITE);

    cout << "Освобождение ресурсов..." << endl;
    // закрытие дескрипторов потока
    for (int i = 0; i < size; i++) {
        CloseHandle(threads[i]);
    }

    DeleteCriticalSection(&criticalSection); // освобождение ресурсов критической секции

    cout << "Все потоки завершены" << endl;
    return 0;
}