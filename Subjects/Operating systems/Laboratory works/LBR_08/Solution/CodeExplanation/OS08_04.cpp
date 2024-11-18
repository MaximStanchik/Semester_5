#include <iostream> // Подключение библиотеки для ввода и вывода
#include <windows.h> // Подключение библиотеки Windows API для работы с кучей

using namespace std; // Использование пространства имен std

void sh(HANDLE heap); // Объявление функции для отображения информации о куче

int main() { // Основная функция программы
    setlocale(LC_ALL, "Rus"); // Установка русской локали для корректного вывода

    HANDLE heap = GetProcessHeap(); // Получение дескриптора кучи процесса
    if (heap == nullptr) { // Проверка, успешно ли получен дескриптор
        cerr << "Ошибка получения дескриптора кучи." << endl; // Вывод сообщения об ошибке
        return 1; // Завершение программы с кодом ошибки
    }

    cout << "До размещения массива: " << endl; // Сообщение перед размещением массива
    sh(heap); // Вызов функции для отображения информации о куче

    int const size = 300000; // Определение размера массива
    int* newArray = (int*)HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, size * sizeof(int)); // Выделение памяти для массива в куче
    if (newArray == nullptr) { // Проверка успешности выделения памяти
        cerr << "Ошибка размещения массива в куче." << endl; // Вывод сообщения об ошибке
        return 1; // Завершение программы с кодом ошибки
    }

    cout << "После размещения массива: " << endl; // Сообщение после размещения массива
    sh(heap); // Вызов функции для отображения информации о куче

    HeapFree(heap, 0, newArray); // Освобождение выделенной памяти в куче

    return 0; // Завершение программы с кодом успеха
}

// Функция для отображения информации о куче
void sh(HANDLE heap) {
    PROCESS_HEAP_ENTRY entry; // Структура для хранения информации о записи в куче
    entry.lpData = nullptr; // Инициализация указателя на данные

    SIZE_T allocatedMemorySize = 0; // Переменная для хранения размера выделенной памяти
    SIZE_T unallocatedMemorySize = 0; // Переменная для хранения размера невыделенной памяти

    // Цикл по всем записям в куче
    while (HeapWalk(heap, &entry)) {
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) { // Проверка, занята ли запись
            allocatedMemorySize += entry.cbData; // Добавление размера выделенной памяти
        }
        else {
            unallocatedMemorySize += entry.cbData; // Добавление размера невыделенной памяти
        }
    }

    SIZE_T totalHeapSize = allocatedMemorySize + unallocatedMemorySize; // Общий размер кучи

    // Вывод информации о куче
    cout << "Общий размер heap: " << totalHeapSize << " байт" << endl;
    cout << "Размер распределенной области памяти heap: " << allocatedMemorySize << " байт" << endl;
    cout << "Размер нераспределенной области памяти heap: " << unallocatedMemorySize << " байт" << endl;
}