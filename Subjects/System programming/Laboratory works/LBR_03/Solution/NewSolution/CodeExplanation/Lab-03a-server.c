#include <stdio.h> // подключение библиотеки для работы с вводом-выводом
#include <stdlib.h> // подключение стандартной библиотеки для работы с функциями С
#include <windows.h>  // подключение библиотеки Windows API
#include <stdbool.h> // подключение библиотеки для работы с булевыми типами

void create_child_process(int lower, int upper, HANDLE hWrite, const char* mutex_name) // Функция для создания дочернего процесса
{
    char cmd[256]; // Буфер для команды запуска процесса
    snprintf(cmd, sizeof(cmd), "Lab-03a-client.exe %d %d %s", lower, upper, mutex_name); // Формирование строки команды

    STARTUPINFO si; // Структура для информации о процессе
    PROCESS_INFORMATION processInfo; // Структура для информации о запущенном процессе
    ZeroMemory(&si, sizeof(STARTUPINFO)); // Обнуление структуры
    si.cb = sizeof(STARTUPINFO); // Установка размера структуры
    si.hStdOutput = hWrite; // Передача дескриптора записи в поток
    si.dwFlags |= STARTF_USESTDHANDLES; // Флаг для использования стандартных дескрипторов
    ZeroMemory(&processInfo, sizeof(processInfo)); // Обнуление структуры процесса

    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &processInfo))  // Создание процесса
    {
        fprintf(stderr, "Error creating child process: %lu\n", GetLastError()); // Сообщение об ошибке
    }
    else {
        printf("Process created\n"); // Сообщение что все ок
        CloseHandle(processInfo.hProcess); // Закрытие дескриптора процесса
        CloseHandle(processInfo.hThread); // Закрытие дескриптора потока
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) { // Проверка количества аргументов
        fprintf(stderr, "Usage: %s <Num Processes> <Lower Bound> <Upper Bound> [Mutex Name]\n", argv[0]);
        return EXIT_FAILURE; // вывод ошибки
    }

    int num_processes = atoi(argv[1]); // Количество процессов
    int lower = atoi(argv[2]); // Нижний предел диапазона
    int upper = atoi(argv[3]); // Верхний предел диапазона
    const char* mutex_name = (argc == 5) ? argv[4] : "DefaultMutex"; // Имя мьютекса или значение по умолчанию

    HANDLE hMutex = CreateMutex(NULL, FALSE, mutex_name); // Создание мьютекса
    if (!hMutex) { // Проверка успешности создания
        fprintf(stderr, "Error creating mutex: %lu\n", GetLastError()); // Сообщение об ошибке
        return EXIT_FAILURE; // Выход с ошибкой
    }

    HANDLE* pipesReadHandles = malloc(sizeof(HANDLE) * num_processes); // Массив для хранения дескрипторов чтения
    if (pipesReadHandles == NULL) { // Проверка успешности выделения памяти
        fprintf(stderr, "Memory allocation error\n"); // Сообщение об ошибке
        CloseHandle(hMutex); // Закрытие мьютекса
        return EXIT_FAILURE; // Выход с ошибкой
    }
 
    // Создание анонимных каналов и запуск дочерних процессов
    for (int i = 0; i < num_processes; i++) {
        HANDLE hWrite; // Дескриптор записи в канал
        SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE }; // Атрибуты безопасности
        if (!CreatePipe(&pipesReadHandles[i], &hWrite, &sa, 0)) { // Создание анонимного канала
            fprintf(stderr, "Error creating pipe: %lu\n", GetLastError()); // Сообщение об ошибке
            CloseHandle(hMutex); // Закрытие мьютекса
            free(pipesReadHandles); // Освобождение памяти
            return EXIT_FAILURE; // Выход с ошибкой
        }
        printf("Creating child process %d...\n", i + 1); // Сообщение о создании процесса
        create_child_process(lower, upper, hWrite, mutex_name); // Вызов функции создания процесса
        CloseHandle(hWrite); // Закрытие дескриптора записи
    }

    Sleep(1000); // Ожидание 

    for (int i = 0; i < num_processes; i++) {
        WaitForSingleObject(hMutex, INFINITE); // Ожидание освобождения мьютекса
        DWORD bytesRead; // Количество прочитанных байт
        int count = 0; // Количество простых чисел
        int* primes = NULL; // Указатель на массив простых чисел

        if (ReadFile(pipesReadHandles[i], &count, sizeof(count), &bytesRead, NULL) && bytesRead == sizeof(count)) { // Чтение количества простых чисел
            ReleaseMutex(hMutex); // Освобождение мьютекса
            printf("Count of primes: %d\n", count); // Вывод количества простых чисел

            if (count > 0) {
                primes = malloc(count * sizeof(int)); // Выделение памяти для массива простых чисел
                Sleep(1000); // Ожидание (можно удалить в реальном приложении)
                WaitForSingleObject(hMutex, INFINITE); // Ожидание освобождения мьютекса

                if (primes && ReadFile(pipesReadHandles[i], primes, sizeof(int) * count, &bytesRead, NULL) && bytesRead == sizeof(int) * count) { // Чтение простых чисел
                    ReleaseMutex(hMutex); // Освобождение мьютекса
                    printf("Process %d found primes:\n", i + 1); // Сообщение о найденных простых числах
                    for (int j = 0; j < count; j++) {
                        printf("%d ", primes[j]); // Вывод простого числа
                    }
                    printf("\n");
                } else {
                    fprintf(stderr, "Error reading primes from pipe: %lu\n", GetLastError()); // Сообщение об ошибке чтения
                }
                free(primes); // Освобождение памяти
            }
        }
        else {
            fprintf(stderr, "Error reading count from pipe for process %d: %lu\n", i + 1, GetLastError()); // Сообщение об ошибке чтения
        }

        ReleaseMutex(hMutex); // Освобождение мьютекса
        CloseHandle(pipesReadHandles[i]); // Закрытие дескриптора чтения
    }

    free(pipesReadHandles); // Освобождение памяти массива дескрипторов
    CloseHandle(hMutex); // Закрытие мьютекса
    return EXIT_SUCCESS; // Успешное завершение программы
}
