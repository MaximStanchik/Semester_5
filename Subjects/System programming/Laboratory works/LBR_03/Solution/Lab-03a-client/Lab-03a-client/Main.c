#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

// Функция для проверки простого числа
int isPrime(int number) {
    if (number <= 1) {
        return 0;
    }
    for (int i = 2; i <= sqrt(number); ++i) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    // Проверка количества аргументов командной строки
    if (argc < 3 || argc > 4) {
        printf("There should be three parameters in total on the command line. The fourth parameter (mutex name) is optional\n");
        return 1;
    }

    int startOfRangeValue = atoi(argv[1]);
    int endOfRangeValue = atoi(argv[2]);
    const char* mutexName = (argc == 4) ? argv[3] : "DefaultMutex";

    // Открытие мьютекса
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, mutexName);
    if (hMutex == NULL) {
        printf("OpenMutex failed (%d).\n", GetLastError());
        return 1;
    }

    // Выделение памяти для буфера простых чисел
    int* buffer = (int*)malloc((endOfRangeValue - startOfRangeValue + 1) * sizeof(int));
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        CloseHandle(hMutex);
        return 1;
    }

    int count = 0;
    printf("Searching for prime numbers...\n");

    // Поиск простых чисел в заданном диапазоне
    for (int number = startOfRangeValue; number <= endOfRangeValue; number++) {
        if (isPrime(number)) {
            buffer[count++] = number;
        }
    }

    // Синхронизация доступа к каналу через мьютекс
    WaitForSingleObject(hMutex, INFINITE);

    // Получение дескриптора канала записи
    HANDLE hWritePipe = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hWritePipe == INVALID_HANDLE_VALUE) {
        printf("Failed to get handle (%d).\n", GetLastError());
        free(buffer);
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        return 1;
    }

    // Запись найденных простых чисел в канал
    for (int i = 0; i < count; i++) {
        DWORD bytesWritten;
        WriteFile(hWritePipe, &buffer[i], sizeof(int), &bytesWritten, NULL);
    }

    // Освобождение ресурсов
    free(buffer);
    CloseHandle(hWritePipe);
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);

    return 0;
}
