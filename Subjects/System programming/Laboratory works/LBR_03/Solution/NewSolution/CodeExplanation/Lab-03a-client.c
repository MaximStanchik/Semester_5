#include <stdio.h> // подключение библиотеки для работы с вводом-выводом
#include <stdlib.h> // подключение стандартной библиотеки для работы с функциями С
#include <windows.h> // подключение библиотеки Windows API
#include <stdbool.h> // подключение библиотеки для работы с булевыми типами

#define MAX_PRIMES 1024 // определение максимального количества простых чисел

bool is_prime(int num) { // функция для проверки, является ли число простым
    if (num < 2) { // если число меньше 2, то оно не может быть простым
        return false;
    }
    for (int i = 2; i * i <= num; i++) { // цикл проверки делителей до квадратного корня из числа
        if (num % i == 0) { // если число делится на i без остатка...
            return false; // то число не простое
        }
    }
    return true; // число простое
}

int main(int argc, char* argv[])
{
    if (argc < 4) { // проверка, что введено достаточное кол-во аргументов
        fprintf(stderr, "Usage: %s <Lower Bound> <Upper Bound> <Mutex Name>\n", argv[0]); // сообщение об ошибке
        return EXIT_FAILURE; // завершение с кодом ошибки
    }

    int lower = atoi(argv[1]); // преобразование первого аргумента в нижний предел
    int upper = atoi(argv[2]); // преобразование второго аргумента в верхний предел 
    const char* mutex_name = argv[3]; // получение имени мьютекса из третьего аргумента

    HANDLE hWrite = GetStdHandle(STD_OUTPUT_HANDLE); // получение дескриптора стандартного вывода
    if (hWrite == INVALID_HANDLE_VALUE) { // проверка на ошибку получения дескриптора
        fprintf(stderr, "Error getting standard output handle: %lu\n", GetLastError()); // сообщение об ошибке
        return EXIT_FAILURE; // завершение пргограммы с кодом ошибки
    }

    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, mutex_name); // открытие мьютекса
    if (hMutex == NULL) { // если мьютекс не открылся
        fprintf(stderr, "Error opening mutex '%s': %lu\n", mutex_name, GetLastError()); // сообщение об ошибке
        return EXIT_FAILURE; // завершение программы с кодом ошибки
    }

    int primes[MAX_PRIMES]; // массив для хранения простых чисел
    int count = 0; // счетчик простых чисел

    for (int i = lower; i <= upper; i++) { // поиск простых чисел в заданном диапазоне
        if (is_prime(i) && count < MAX_PRIMES) { // проверка что число простое и не превышено ограничение массива
            primes[count++] = i; // сохранение простого числа в массиве
        } 
    }

    WaitForSingleObject(hMutex, INFINITE); // ожидание пока мьютекс станет свободным         

    DWORD written; // переменная для хранения кол-ва описанных байт
    if (WriteFile(hWrite, &count, sizeof(count), &written, NULL) && written == sizeof(count)) {
        ReleaseMutex(hMutex); // освобождение мьютекса
        Sleep(1000); // задержка на 1 секунду
        WaitForSingleObject(hMutex, INFINITE); // ожидание пока мьютекс станет свободным
        WriteFile(hWrite, primes, sizeof(int) * count, &written, NULL); // запись массива простых чисел
    }
    else 
    {
        fprintf(stderr, "Error writing primes to pipe\n"); // вывод сообщения об ошибке
    }

    ReleaseMutex(hMutex); // освобождение мьютекса
    CloseHandle(hWrite); // закрытие дескриптора стандартного вывода
    CloseHandle(hMutex); // закрытие дескриптора мьютекса

    return EXIT_SUCCESS; // успешное завершение программы
}


// пояснение параметров некоторых функций:

// WaitForSingleObject(hMutex, INFINITE);
// hMutex -- дескриптор объекта синхронизации (в данном случае мьютекса), доступ к которому можно получить 
// INFINITE -- время ожидания в миллисекундах. Значние INFINITE указывает, что функция будет ждать бесконечно долго, пока объект не станет доступным

// WriteFile(hWrite, primes, sizeof(int) * count, &written, NULL);
// hWrite: Дескриптор файла или потока, в который производится запись. Здесь это стандартный вывод.
// &count: Указатель на буфер, содержащий данные для записи (в данном случае — количество простых чисел).
// sizeof(count): Количество байт для записи. Здесь размер типа int.
// &written: Указатель на переменную, куда будет записано количество реально записанных байт.
// NULL: Указатель на структуру OVERLAPPED, используемую для асинхронных операций. Здесь NULL, так как запись синхронная.