#include <stdio.h> // Подключение библиотеки для работы с вводом-выводом
#include <stdlib.h> // Подключение библиотеки для работы с функциями общего назначения
#include <windows.h> // Подключение библиотеки Windows API
#include <stdbool.h> // Подключение библиотеки для работы с булевыми значениями
#define BUFFER_SIZE 256 // Определение размера буфера для чтения/записи

//ClientB
int main(int argc, char* argv[]) {
    const char* str = argv[1]; // Считывание строки из аргументов командной строки
    const char* name_pipe; // Переменная для имени канала

    // Установка имени канала в зависимости от количества аргументов
    if (argc == 3 || argc == 4) {
        name_pipe = argv[2]; // Если передано два или три аргумента, используем второй как имя канала
    } 
    else {
        name_pipe = "DefaultPipe"; // Если аргументы не заданы, используем значение по умолчанию
    }

    const char* name_semaphore; // Переменная для имени семафора
    // Установка имени семафора в зависимости от количества аргументов
    if (argc == 4) {
        name_semaphore = argv[3]; // Если передан третий аргумент, используем его как имя семафора
    } else {
        name_semaphore = "DefaultSemaphore"; // Если нет, используем значение по умолчанию
    }

    char full_pipe_name[256]; // Массив для полного имени канала
    // Формирование полного имени канала
    snprintf(full_pipe_name, sizeof(full_pipe_name), "\\\\.\\pipe\\%s", name_pipe);

    // Открытие семафора с указанным именем
    HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE, FALSE, name_semaphore);
    if (hSemaphore == NULL) { // Если семафор не найден
        // Создание нового семафора
        hSemaphore = CreateSemaphore(NULL, 1, 1, name_semaphore);
        if (hSemaphore == NULL) { // Проверка на ошибку создания семафора
            printf("Error: Could not create semaphore '%s'. Error code: %lu\n", name_semaphore, GetLastError());
            return EXIT_FAILURE; // Завершение работы с ошибкой
        }
        printf("Semaphore '%s' created by client.\n", name_semaphore); // Успешное создание семафора
    } else {
        printf("Semaphore '%s' opened by client.\n", name_semaphore); // Успешное открытие семафора
    }

    // Ожидание получения доступа к семафору
    DWORD waitResult = WaitForSingleObject(hSemaphore, INFINITE);
    if (waitResult != WAIT_OBJECT_0) { // Проверка на успешное ожидание
        printf("Error: Failed to wait for semaphore. Error code: %lu\n", GetLastError());
        return EXIT_FAILURE; // Завершение работы с ошибкой
    }

    // Открытие именованного канала для связи
    HANDLE hPipe = CreateFile(
        full_pipe_name, // Полное имя канала
        GENERIC_WRITE | GENERIC_READ, // Открытие для чтения и записи
        0, // Нет совместного доступа
        NULL, // Без атрибутов безопасности
        OPEN_EXISTING, // Открытие существующего канала
        0, // Без дополнительных атрибутов
        NULL // Без шаблона
    );

    if (hPipe == INVALID_HANDLE_VALUE) { // Проверка на успешное открытие канала
        printf("Error: Could not open pipe '%s'. Error code: %lu\n", name_pipe, GetLastError());
        return EXIT_FAILURE; // Завершение работы с ошибкой
    }

    // Генерация случайной задержки перед отправкой
    int randomSleepTime = rand() % 2000 + 1000; // Задержка от 1 до 3 секунд
    Sleep(randomSleepTime); // Ожидание

    // Подготовка данных для отправки
    DWORD bytesToSend = strlen(str) + 1; // Длина строки с учетом завершающего нуля
    DWORD bytesWritten = 0; // Переменная для хранения количества записанных байтов

    // Запись длины строки в канал
    if (!WriteFile(hPipe, &bytesToSend, sizeof(bytesToSend), &bytesWritten, NULL)) {
        printf("Error: Failed to write length to pipe. Error code: %lu\n", GetLastError());
        ReleaseSemaphore(hSemaphore, 1, NULL); // Освобождение семафора
        return EXIT_FAILURE; // Завершение работы с ошибкой
    }

    // Запись строки в канал
    if (!WriteFile(hPipe, str, strlen(str) + 1, &bytesWritten, NULL)) {
        printf("Pipe closed because of buffer overflow\n"); // Сообщение об ошибке переполнения буфера
        ReleaseSemaphore(hSemaphore, 1, NULL); // Освобождение семафора
        return EXIT_FAILURE; // Завершение работы с ошибкой
    }

    char buffer[BUFFER_SIZE]; // Буфер для чтения ответа
    DWORD bytesRead; // Переменная для хранения количества прочитанных байтов

    // Чтение ответа из канала
    if (ReadFile(hPipe, buffer, BUFFER_SIZE - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0'; // Завершение строки
        printf("Received response: %s\n", buffer); // Вывод полученного ответа
    } else {
        printf("Error: Failed to read from pipe. Error code: %lu\n", GetLastError()); // Сообщение об ошибке чтения
    }

    ReleaseSemaphore(hSemaphore, 1, NULL); // Освобождение семафора
    CloseHandle(hPipe); // Закрытие дескриптора канала
    CloseHandle(hSemaphore); // Закрытие дескриптора семафора
    return EXIT_SUCCESS; // Успешное завершение программы
}