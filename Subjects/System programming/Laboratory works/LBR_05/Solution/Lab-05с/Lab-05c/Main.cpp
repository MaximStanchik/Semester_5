#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define INITIAL_HEAP_SIZE (1024 * 1024)  // 1 ฬ่ม
#define MAX_HEAP_SIZE (8 * 1024 * 1024)  // 8 ฬ่ม
#define NUM_BLOCKS 5
#define BLOCK_SIZE (1024 * 1024)  // 1 ฬ่ม

void HeapInfo(HANDLE heap) {
    PROCESS_HEAP_ENTRY entry;
    entry.lpData = NULL;

    printf("\nHeap Information:\n");

    SIZE_T totalSize = 0;
    while (HeapWalk(heap, &entry)) {
        printf("Address: %p, Size: %zu, Type: ", entry.lpData, entry.cbData);
        switch (entry.wFlags & ~PROCESS_HEAP_ENTRY_BUSY) {
        case 0:
            printf("Free\n");
            break;
        case PROCESS_HEAP_ENTRY_BUSY:
            printf("Allocated\n");
            break;
        case PROCESS_HEAP_ENTRY_MOVEABLE:
            printf("Moveable\n");
            break;
        case PROCESS_HEAP_ENTRY_DDESHARE:
            printf("DDE Share\n");
            break;
        default:
            printf("Unknown\n");
            break;
        }
        totalSize += entry.cbData;
    }

    printf("Total Heap Size: %zu bytes\n", totalSize);
}

int main() {
    DWORD pid = GetCurrentProcessId();
    printf("Current Process ID: %lu\n", pid);

    HANDLE heap = HeapCreate(0, INITIAL_HEAP_SIZE, MAX_HEAP_SIZE);
    if (heap == NULL) {
        printf("Error creating heap: %lu\n", GetLastError());
        return 1;
    }
    printf("Heap created successfully.\n");
    HeapInfo(heap);

    for (int i = 0; i < NUM_BLOCKS; i++) {
        void* block = HeapAlloc(heap, 0, BLOCK_SIZE);
        if (block == NULL) {
            printf("Error allocating memory: %lu\n", GetLastError());
            HeapDestroy(heap);
            return 1;
        }

        printf("Block %d allocated at %p.\n", i + 1, block);
        HeapInfo(heap);
    }

    printf("All blocks allocated.\n");
    printf("Press Enter to continue...\n");
    getchar();

    for (int i = 0; i < NUM_BLOCKS; i++) {
        void* block = HeapAlloc(heap, 0, BLOCK_SIZE);
        if (block == NULL) {
            printf("Error allocating memory: %lu\n", GetLastError());
            HeapDestroy(heap);
            return 1;
        }

        if (!HeapFree(heap, 0, block)) {
            printf("Error freeing memory: %lu\n", GetLastError());
            HeapDestroy(heap);
            return 1;
        }

        printf("Block %d freed.\n", i + 1);
        HeapInfo(heap);
    }

    printf("All blocks freed.\n");
    printf("Press Enter to continue...\n");
    getchar();

    if (!HeapDestroy(heap)) {
        printf("Error destroying heap: %lu\n", GetLastError());
        return 1;
    }

    printf("Heap destroyed successfully.\n");

    return 0;
}