#include <stdio.h>
#include <windows.h>

int countSum(int num_1, int num_2) {
    return num_1 + num_2;
}

int glInitVar = 10;
int glUninitVar;

int static statGlInitVar = 20;
int static statGlUninitVar;

int main(int argc, char* argv[]) {

    DWORD processID = GetCurrentProcessId();

    printf("Process ID: %lu\n", processID);

    int locInitVar = 30;
    int locUninitVar;

    int static staticLocInitVar = 40;
    int static staticLocUninitVar;

    printf("Address of a global initialized variable: %p\n", (void*)&glInitVar);
    printf("Address of a global uninitialized variable: %p\n", (void*)&glUninitVar);
    printf("Address of a global static initialized variable: %p\n", (void*)&statGlInitVar);
    printf("Address of a global static uninitialized variable: %p\n", (void*)&statGlUninitVar);

    printf("Address of local initialized variable: %p\n", (void*)&locInitVar);
    printf("Address of local uninitialized variable: %p\n", (void*)&locUninitVar);
    printf("Address of a local static initialized variable: %p\n", (void*)&staticLocInitVar);
    printf("Address of a local static uninitialized variable: %p\n", (void*)&staticLocUninitVar);

    printf("Address argc (number of command line arguments): %p\n", (void*)&argc);
    printf("Address argv (command line arguments): %p\n", (void*)&argv);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}