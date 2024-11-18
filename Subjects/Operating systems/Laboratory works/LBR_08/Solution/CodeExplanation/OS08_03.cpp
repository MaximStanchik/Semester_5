#include <iostream> // Подключение библиотеки для ввода и вывода
#include <windows.h> // Подключение библиотеки Windows для работы с функциями Windows API
#include <cstring> // Подключение библиотеки для работы с C-строками и функциями memcpy

using namespace std; // Использование пространства имен std для упрощения кода

#define KB (1024) // Определение макроса для 1 КБ
#define MB (1024 * KB) // Определение макроса для 1 МБ
#define PG (4 * KB) // Определение макроса для размера страницы (4 КБ)

void getInfoAboutCompMem() { // Функция для получения информации о памяти компьютера
    MEMORYSTATUS ms; // Создание структуры для хранения информации о памяти
    GlobalMemoryStatus(&ms); // Получение информации о памяти системы
    cout << "Объём физической памяти:      " << ms.dwTotalPhys / KB << " KB\n"; // Вывод общего объема физической памяти
    cout << "Доступно физической памяти:   " << ms.dwAvailPhys / KB << " KB\n"; // Вывод доступного объема физической памяти
    cout << "Объем виртуальной памяти:     " << ms.dwTotalVirtual / KB << " KB\n"; // Вывод общего объема виртуальной памяти
    cout << "Доступно виртуальной памяти:  " << ms.dwAvailVirtual / KB << " KB\n\n"; // Вывод доступного объема виртуальной памяти
}

int main() { // Основная функция программы
    setlocale(LC_ALL, "Rus"); // Установка русской локали для корректного вывода

    const size_t pageSize = 4096; // Размер страницы (4 КБ)
    const size_t pageCount = 256; // Количество страниц
    const size_t totalMemorySize = pageSize * pageCount; // Общий размер выделяемой памяти

    cout << "Информация о памяти компьютера:" << endl; // Вывод заголовка
    getInfoAboutCompMem(); // Вызов функции для получения информации о памяти

    // Выделение виртуальной памяти
    LPVOID allocatedMemory = VirtualAlloc(nullptr, totalMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (allocatedMemory == nullptr) { // Проверка, успешно ли выделена память
        cerr << "Ошибка выделения памяти: " << GetLastError() << endl; // Вывод сообщения об ошибке
        return 1; // Завершение программы с кодом ошибки
    }

    cout << "Успешно выделено " << totalMemorySize << " байт (" << pageCount << " страниц)." << endl; // Подтверждение успешного выделения памяти

    int* arrayOfNumbers = (int*)allocatedMemory; // Приведение выделенной памяти к указателю на целые числа
    for (int i = 0; i < totalMemorySize / sizeof(int); ++i) { // Заполнение массива целыми числами
        arrayOfNumbers[i] = static_cast<int>(i); // Присвоение значений элементам массива
    }

    const char lastName[] = { 0xD0, 0xA1, 0xD1, 0x82, 0xD0, 0xB0 }; // Инициализация массива символов (например, "Стана" в UTF-8)
    memcpy(arrayOfNumbers, lastName, sizeof(lastName)); // Копирование массива символов в начало выделенной памяти

    const int pageNumber = 208; // Номер страницы для доступа
    const int offset = 3630; // Смещение в байтах для доступа

    if (pageNumber < pageCount && offset < pageSize) { // Проверка, находятся ли номер страницы и смещение в допустимых пределах
        // Вычисление адреса в выделенной памяти с учетом номера страницы и смещения
        int* byte = arrayOfNumbers + (pageNumber * (pageSize / sizeof(int))) + (offset / sizeof(int));
        cout << "------  Значение памяти в байте: " << *byte << "  ------\n"; // Вывод значения памяти по вычисленному адресу
    }
    else {
        cout << "Ошибка: номер страницы или смещение выходят за пределы выделенной памяти." << endl; // Сообщение об ошибке
    }

    // Освобождение выделенной памяти
    if (!VirtualFree(allocatedMemory, 0, MEM_RELEASE)) { 
        cerr << "Ошибка освобождения памяти: " << GetLastError() << endl; // Вывод сообщения об ошибке
        return 1; // Завершение программы с кодом ошибки
    }

    cout << "Память успешно освобождена." << endl; // Подтверждение освобождения памяти
    cout << "Информация о памяти компьютера:" << endl; // Заголовок для информации о памяти
    getInfoAboutCompMem(); // Повторный вызов функции для получения информации о памяти

    return 0; // Завершение программы с кодом успеха
}