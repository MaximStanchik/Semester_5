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
    cout << "����� ���������� ������:      " << ms.dwTotalPhys / KB << " KB\n";
    cout << "�������� ���������� ������:   " << ms.dwAvailPhys / KB << " KB\n";
    cout << "����� ����������� ������:     " << ms.dwTotalVirtual / KB << " KB\n";
    cout << "�������� ����������� ������:  " << ms.dwAvailVirtual / KB << " KB\n\n";
}

int main() {
    setlocale(LC_ALL, "Rus");

    const size_t pageSize = 4096;
    const size_t pageCount = 256;
    const size_t totalMemorySize = pageSize * pageCount; 

    cout << "���������� � ������ ����������:" << endl;
    getInfoAboutCompMem();

    LPVOID allocatedMemory = VirtualAlloc(nullptr, totalMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (allocatedMemory == nullptr) {
        cerr << "������ ��������� ������: " << GetLastError() << endl;
        return 1;
    }

    cout << "������� �������� " << totalMemorySize << " ���� (" << pageCount << " �������)." << endl;

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
        cout << "------  �������� ������ � �����: " << *byte << "  ------\n";
    }
    else {
        cout << "������: ����� �������� ��� �������� ������� �� ������� ���������� ������." << endl;
    }

    if (!VirtualFree(allocatedMemory, 0, MEM_RELEASE)) {
        cerr << "������ ������������ ������: " << GetLastError() << endl;
        return 1;
    }

    cout << "������ ������� �����������." << endl;
    cout << "���������� � ������ ����������:" << endl;
    getInfoAboutCompMem();

    return 0;
}