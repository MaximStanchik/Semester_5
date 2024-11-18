#include <iostream>
#include <windows.h>
#include <cstring>

using namespace std;

#define KB (1024)
#define MB (1024 * KB)
#define PG (4 * KB)

void getInfoAboutCompMem() {
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    cout << "Объём физической памяти:      " << ms.dwTotalPhys / KB << " KB\n";
    cout << "Доступно физической памяти:   " << ms.dwAvailPhys / KB << " KB\n";
    cout << "Объем виртуальной памяти:     " << ms.dwTotalVirtual / KB << " KB\n";
    cout << "Доступно виртуальной памяти:  " << ms.dwAvailVirtual / KB << " KB\n\n";
}

int main() {
    setlocale(LC_ALL, "Rus");

    const size_t pageSize = 4096;
    const size_t pageCount = 256;
    const size_t totalMemorySize = pageSize * pageCount; 

    cout << "Информация о памяти компьютера:" << endl;
    getInfoAboutCompMem();

    LPVOID allocatedMemory = VirtualAlloc(nullptr, totalMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (allocatedMemory == nullptr) {
        cerr << "Ошибка выделения памяти: " << GetLastError() << endl;
        return 1;
    }

    cout << "Успешно выделено " << totalMemorySize << " байт (" << pageCount << " страниц)." << endl;

    int* arrayOfNumbers = (int*)allocatedMemory;
    for (int i = 0; i < totalMemorySize / sizeof(int); ++i) {
        arrayOfNumbers[i] = static_cast<int>(i);
    }

    const char lastName[] = { 0xD0, 0xA1, 0xD1, 0x82, 0xD0, 0xB0 };
    memcpy(arrayOfNumbers, lastName, sizeof(lastName)); 

    const int pageNumber = 208;       
    const int offset = 3630;

    if (pageNumber < pageCount && offset < pageSize) {
        int* byte = arrayOfNumbers + (pageNumber * (pageSize / sizeof(int))) + (offset / sizeof(int));
        cout << "------  Значение памяти в байте: " << *byte << "  ------\n";
    }
    else {
        cout << "Ошибка: номер страницы или смещение выходят за пределы выделенной памяти." << endl;
    }

    if (!VirtualFree(allocatedMemory, 0, MEM_RELEASE)) {
        cerr << "Ошибка освобождения памяти: " << GetLastError() << endl;
        return 1;
    }

    cout << "Память успешно освобождена." << endl;
    cout << "Информация о памяти компьютера:" << endl;
    getInfoAboutCompMem();

    return 0;
}