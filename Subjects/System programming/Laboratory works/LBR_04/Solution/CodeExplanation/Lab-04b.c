#include <stdio.h>               // Подключение стандартной библиотеки для работы с вводом и выводом
#include <windows.h>              // Подключение библиотеки Windows для работы с потоками и критическими секциями

#define MAX_PRIMES 1000           // Определение максимального количества простых чисел, которые можно сохранить

typedef struct {                  // Определение структуры для передачи данных в поток
    int lower;                    // Нижняя граница диапазона поиска простых чисел
    int upper;                    // Верхняя граница диапазона поиска простых чисел
    int threadId;                 // Идентификатор потока
} ThreadData;

CRITICAL_SECTION cs;              // Критическая секция для синхронизации доступа к общим данным
int globalPrimes[MAX_PRIMES];     // Глобальный массив для хранения найденных простых чисел
int primeCount = 0;               // Количество найденных простых чисел
DWORD tlsIndex;                   // Индекс для хранения локальных данных в TLS (памяти потока)

DWORD WINAPI L4Thread(LPVOID param) {          // Функция потока для поиска простых чисел
    ThreadData* data = (ThreadData*)param;     // Приведение параметра к типу ThreadData

    int* localPrimes = (int*)malloc(MAX_PRIMES * sizeof(int));  // Выделение памяти для локального массива простых чисел
    if (!localPrimes) {                         // Проверка успешного выделения памяти
        fprintf(stderr, "Error allocating memory for localPrimes\n");  // Вывод ошибки, если память не выделена
        return 1;                               // Завершение потока с ошибкой
    }

    if (!TlsSetValue(tlsIndex, localPrimes)) {  // Установка локального массива в TLS для текущего потока
        fprintf(stderr, "Error setting TLS value\n");  // Сообщение об ошибке, если установка не удалась
        free(localPrimes);                       // Освобождение памяти, если установка не удалась
        return 1;                                // Завершение потока с ошибкой
    }

    int localCount = 0;                          // Локальный счетчик простых чисел
    for (int i = data->lower; i <= data->upper; i++) {  // Цикл по диапазону чисел для проверки
        if (isPrime(i)) {                        // Проверка, является ли число простым
            if (localCount < MAX_PRIMES) {       // Проверка, что локальный массив не заполнен
                localPrimes[localCount++] = i;   // Сохранение простого числа в локальный массив
            }
        }
    }

    EnterCriticalSection(&cs);                   // Вход в критическую секцию для безопасного доступа к глобальному массиву
    for (int i = 0; i < localCount; i++) {       // Копирование локальных простых чисел в глобальный массив
        if (primeCount < MAX_PRIMES) {           // Проверка, что глобальный массив не заполнен
            globalPrimes[primeCount++] = localPrimes[i];  // Добавление числа в глобальный массив
        }
    }
    LeaveCriticalSection(&cs);                   // Выход из критической секции

    free(localPrimes);                           // Освобождение памяти, выделенной для локального массива
    return 0;                                    // Завершение потока без ошибки
}

int isPrime(int num) {                           // Функция проверки, является ли число простым
    if (num < 2) return 0;                       // Числа меньше 2 не являются простыми
    for (int i = 2; i * i <= num; i++) {         // Цикл от 2 до корня из числа
        if (num % i == 0) return 0;              // Если число делится на i, оно не является простым
    }
    return 1;                                    // Если делителей нет, число простое
}

int main(int argc, char* argv[]) {               // Главная функция
    if (argc != 4) {                             // Проверка количества аргументов командной строки
        fprintf(stderr, "Usage: %s <Number of threads> <Lower range> <Upper range>\n", argv[0]);  // Вывод информации о правильном использовании
        return EXIT_FAILURE;                     // Завершение программы с ошибкой
    }

    int numberOfThreads = atoi(argv[1]);         // Преобразование аргумента в количество потоков
    int lower = atoi(argv[2]);                   // Преобразование аргумента в нижний диапазон поиска
    int upper = atoi(argv[3]);                   // Преобразование аргумента в верхний диапазон поиска

    if (numberOfThreads < 1 || upper < lower) {  // Проверка корректности введенных данных
        fprintf(stderr, "Invalid input.\n");     // Вывод ошибки, если данные некорректны
        return EXIT_FAILURE;                     // Завершение программы с ошибкой
    }

    InitializeCriticalSection(&cs);              // Инициализация критической секции

    tlsIndex = TlsAlloc();                       // Выделение индекса TLS для хранения локальных данных
    if (tlsIndex == TLS_OUT_OF_INDEXES) {        // Проверка успешного выделения TLS индекса
        fprintf(stderr, "Error allocating TLS index\n");  // Сообщение об ошибке, если выделение не удалось
        DeleteCriticalSection(&cs);              // Удаление критической секции
        return EXIT_FAILURE;                     // Завершение программы с ошибкой
    }

    HANDLE* threads = (HANDLE*)malloc(numberOfThreads * sizeof(HANDLE));  // Выделение памяти для хранения дескрипторов потоков
    ThreadData* threadData = (ThreadData*)malloc(numberOfThreads * sizeof(ThreadData));  // Выделение памяти для данных потоков
    if (!threads || !threadData) {               // Проверка успешного выделения памяти
        fprintf(stderr, "Error allocating memory for threads or threadData\n");  // Сообщение об ошибке, если выделение не удалось
        DeleteCriticalSection(&cs);              // Удаление критической секции
        TlsFree(tlsIndex);                       // Освобождение TLS индекса
        if (threads) free(threads);              // Освобождение памяти для дескрипторов потоков, если выделено
        if (threadData) free(threadData);        // Освобождение памяти для данных потоков, если выделено
        return EXIT_FAILURE;                     // Завершение программы с ошибкой
    }

    int range = upper - lower + 1;               // Подсчет общего диапазона чисел
    int partSize = range / numberOfThreads;      // Определение размера диапазона для каждого потока
    int remainder = range % numberOfThreads;     // Подсчет остатка для равномерного распределения диапазонов

    for (int i = 0; i < numberOfThreads; i++) {  // Цикл создания потоков
        threadData[i].lower = lower + i * partSize + (i < remainder ? i : remainder);  // Установка нижней границы для потока
        threadData[i].upper = threadData[i].lower + partSize - 1 + (i < remainder ? 1 : 0);  // Установка верхней границы для потока
        threadData[i].threadId = i + 1;          // Установка идентификатора потока

        threads[i] = CreateThread(NULL, 0, L4Thread, &threadData[i], 0, NULL);  // Создание потока
        if (threads[i] == NULL) {                // Проверка успешного создания потока
            fprintf(stderr, "Error creating thread %d\n", i);  // Сообщение об ошибке, если поток не создан
            for (int j = 0; j < i; j++) CloseHandle(threads[j]);  // Закрытие созданных потоков при ошибке
            DeleteCriticalSection(&cs);          // Удаление критической секции
            TlsFree(tlsIndex);                   // Освобождение TLS индекса
            free(threads);                       // Освобождение памяти для дескрипторов потоков
            free(threadData);                    // Освобождение памяти для данных потоков
            return EXIT_FAILURE;                 // Завершение программы с ошибкой
        }
    }

    WaitForMultipleObjects(numberOfThreads, threads, TRUE, INFINITE);  // Ожидание завершения всех потоков
    for (int i = 0; i < numberOfThreads; i++) {  // Закрытие дескрипторов потоков
        CloseHandle(threads[i]);
    }

    free(threads);                               // Освобождение памяти для дескрипторов потоков
    free(threadData);                            // Освобождение памяти для данных потоков
    TlsFree(tlsIndex);                           // Освобождение TLS индекса

    for (int i = 0; i < primeCount - 1; i++) {   // Сортировка массива простых чисел пузырьковой сортировкой
        for (int j = i + 1; j < primeCount; j++) {
            if (globalPrimes[i] > globalPrimes[j]) {  // Сравнение и обмен значений для сортировки
                int temp = globalPrimes[i];
                globalPrimes[i] = globalPrimes[j];
                globalPrimes[j] = temp;
            }
        }
    }

    printf("Found prime numbers:\n");            // Вывод найденных простых чисел
    for (int i = 0; i < primeCount; i++) {
        printf("%d ", globalPrimes[i]);
    }
    printf("\n");

    DeleteCriticalSection(&cs);                  // Удаление критической секции
    return 0;                                    // Завершение программы
}
