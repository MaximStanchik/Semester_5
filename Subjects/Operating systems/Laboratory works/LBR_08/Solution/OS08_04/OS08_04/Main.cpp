#include <iostream>
#include <windows.h>

using namespace std;

void sh(HANDLE heap);

int main() {
    setlocale(LC_ALL, "Rus");

    HANDLE heap = GetProcessHeap();
    if (heap == nullptr) {
        cerr << "Ошибка получения дескриптора кучи." << endl;
        return 1;
    }

    cout << "До размещения массива: " << endl;
    sh(heap);

    int const size = 300000;
    int* newArray = (int*)HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, size * sizeof(int));
    if (newArray == nullptr) {
        cerr << "Ошибка размещения массива в куче." << endl;
        return 1;
    }

    cout << "После размещения массива: " << endl;
    sh(heap);

    HeapFree(heap, 0, newArray);

    return 0;
}

void sh(HANDLE heap) {
    PROCESS_HEAP_ENTRY entry;
    entry.lpData = nullptr;

    SIZE_T allocatedMemorySize = 0; 
    SIZE_T unallocatedMemorySize = 0;

    while (HeapWalk(heap, &entry)) {
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) {
            allocatedMemorySize = allocatedMemorySize + entry.cbData;
        }
        else {
            unallocatedMemorySize = unallocatedMemorySize + entry.cbData;
        }
    }

    SIZE_T totalHeapSize = allocatedMemorySize + unallocatedMemorySize;

    cout << "Общий размер heap: " << totalHeapSize << " байт" << endl;
    cout << "Размер распределенной области памяти heap: " << allocatedMemorySize << " байт" << endl;
    cout << "Размер нераспределенной области памяти heap: " << unallocatedMemorySize << " байт" << endl;
}