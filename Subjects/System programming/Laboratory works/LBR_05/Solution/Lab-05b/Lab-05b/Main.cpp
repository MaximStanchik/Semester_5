#include <stdio.h>
#include <windows.h>

int main() {
    DWORD pid = GetCurrentProcessId();
    printf("Current Process ID: %lu\n", pid);

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    SIZE_T pageSize = sysInfo.dwPageSize;

    const SIZE_T totalPages = 256;
    const SIZE_T committedPages = 128;

    LPVOID reservedVirtualMemory = VirtualAlloc(NULL, totalPages * pageSize, MEM_RESERVE, PAGE_READWRITE);

    if (reservedVirtualMemory == NULL) {
        printf("Memory reservation error: %lu\n", GetLastError());
        return 1;
    }

    printf("Address of the reserved memory area: %p\n", reservedVirtualMemory);
    printf("Press Enter to continue...\n");
    getchar(); 

    LPVOID committedMemory = VirtualAlloc(
        (LPBYTE)reservedVirtualMemory + (committedPages * pageSize),
        committedPages * pageSize,
        MEM_COMMIT,
        PAGE_READWRITE
    );

    if (committedMemory == NULL) {
        printf("Physical memory allocation error: %lu\n", GetLastError());
        VirtualFree(reservedVirtualMemory, 0, MEM_RELEASE);
        return 1;
    }

    printf("Address of allocated physical memory: %p\n", committedMemory);
    printf("Press Enter to continue...\n");
    getchar(); 

    for (SIZE_T i = 0; i < committedPages * (pageSize / sizeof(int)); i++) {
        *((int*)((LPBYTE)committedMemory + i * sizeof(int))) = (int)i;
    }

    DWORD oldProtect;
    if (!VirtualProtect(committedMemory, committedPages * pageSize, PAGE_READONLY, &oldProtect)) {
        printf("Error changing protection attributes: %lu\n", GetLastError());
        VirtualFree(reservedVirtualMemory, 0, MEM_RELEASE);
        return 1;
    }

    printf("Completed values:\n");
    for (SIZE_T i = 0; i < committedPages * (pageSize / sizeof(int)); i++) {
        printf("%d ", *((int*)((LPBYTE)committedMemory + i * sizeof(int))));
    }
    printf("\nPress Enter to continue...\n");
    getchar(); 

    if (!VirtualFree(committedMemory, committedPages * pageSize, MEM_DECOMMIT)) {
        printf("Error freeing physical memory: %lu\n", GetLastError());
    }
    else {
        printf("Physical memory was successfully freed.\n");
    }
    printf("Press Enter to continue...\n");
    getchar(); 

    if (!VirtualFree(reservedVirtualMemory, 0, MEM_RELEASE)) {
        printf("Error freeing reserved memory: %lu\n", GetLastError());
    }
    else {
        printf("Reserved memory successfully freed.\n");
    }

    return 0;
}