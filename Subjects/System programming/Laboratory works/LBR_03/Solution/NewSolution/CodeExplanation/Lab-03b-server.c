#include <stdio.h> // Подключение библиотеки для работы с вводом-выводом
#include <stdlib.h> // Подключение библиотеки для работы с функциями общего назначения
#include <windows.h> // Подключение библиотеки Windows API
#include <stdbool.h> // Подключение библиотеки для работы с булевыми значениями
#define BUFFER_SIZE 3 // Определение размера буфера для чтения/записи

// Функция для преобразования строки в верхний регистр
void to_uppercase(char* str) {
    while (*str) { // Проход по всем символам строки
        *str = toupper((unsigned char)*str); // Преобразование текущего символа в верхний регистр
        str++; // Переход к следующему символу
    }
}

//ServerB
int main(int argc, char* argv[]) {
    // Установка имени канала в зависимости от количества аргументов
    const char* pipe_name = (argc == 2) ? argv[1] : "DefaultPipe"; // Если передан аргумент, используем его как имя канала

    char full_pipe_name[256]; // Массив для полного имени канала
    // Формирование полного имени канала
    snprintf(full_pipe_name, sizeof(full_pipe_name), "\\\\.\\pipe\\%s", pipe_name);

    // Создание именованного канала для связи
    HANDLE hPipe = CreateNamedPipe(full_pipe_name, // Имя канала
        PIPE_ACCESS_DUPLEX, // Доступ для чтения и записи
        PIPE_TYPE_MESSAGE | PIPE_WAIT, // Тип канала и ожидание
        1, // Максимальное количество экземпляров
        0, // Размер выходного буфера
        0, // Размер входного буфера
        INFINITE, // Ожидание подключения
        NULL); // Без атрибутов безопасности

    if (hPipe == INVALID_HANDLE_VALUE) { // Проверка на успешное создание канала
        printf("Error: Could not create pipe '%s'. Error code: %lu\n", full_pipe_name, GetLastError());
        return EXIT_FAILURE; // Завершение работы с ошибкой
    }

    printf("Server is running and waiting for clients...\n"); // Сообщение о запуске сервера

    while (true) { // Бесконечный цикл для обработки поступающих сообщений
        // Ожидание подключения клиента
        if (!ConnectNamedPipe(hPipe, NULL)) {
            printf("Error: Failed to connect to pipe. Error code: %lu\n", GetLastError());
            CloseHandle(hPipe); // Закрытие канала при ошибке
            return EXIT_FAILURE; // Завершение работы с ошибкой
        }

        char buffer[BUFFER_SIZE]; // Буфер для чтения данных от клиента
        DWORD bytesRead; // Переменная для хранения количества прочитанных байтов
        DWORD bytesToRead; // Переменная для хранения длины строки

        // Чтение длины строки из канала
        if (!ReadFile(hPipe, &bytesToRead, sizeof(bytesToRead), &bytesRead, NULL)) {
            printf("Error: Failed to read length from pipe. Error code: %lu\n", GetLastError());
        }

        // Проверка на переполнение буфера
        if (bytesToRead > BUFFER_SIZE) {
            printf("Error: Buffer overflow\n"); // Сообщение об ошибке переполнения буфера
            DisconnectNamedPipe(hPipe); // Отключение канала
            continue; // Переход к следующему циклу
        }

        // Чтение строки из канала
        if (ReadFile(hPipe, buffer, BUFFER_SIZE - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0'; // Завершение строки
            printf("Received string: %s\n", buffer); // Вывод полученной строки
            to_uppercase(buffer); // Преобразование строки в верхний регистр
            printf("Transformed string: %s\n", buffer); // Вывод преобразованной строки

            DWORD bytesWritten; // Переменная для хранения количества записанных байтов
            // Запись преобразованной строки обратно в канал
            if (!WriteFile(hPipe, buffer, strlen(buffer) + 1, &bytesWritten, NULL))
                printf("Error: Failed to write to pipe. Error code: %lu\n", GetLastError()); // Сообщение об ошибке записи
        } else {
            fprintf(stderr, "Error: Failed to read from pipe. Error code: %lu\n", GetLastError()); // Сообщение об ошибке чтения
        }

        DisconnectNamedPipe(hPipe); // Отключение канала после обработки
    }

    CloseHandle(hPipe); // Закрытие дескриптора канала
    return EXIT_SUCCESS; // Успешное завершение программы
}