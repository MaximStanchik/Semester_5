#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
    int iterations;
    char* envVar = NULL;

    if (argc >= 2) {
        iterations = atoi(argv[1]);
    }
    else {
        size_t size;
        if (_dupenv_s(&envVar, &size, "ITER_NUM") == 0 && envVar != NULL) {
            iterations = atoi(envVar);
            free(envVar);  
        }
        else {
            printf("The number of iterations is not specified\n");
            ExitProcess(1);
        }
    }

    if (iterations <= 0) {
        printf("The number of iterations must be a positive number\n");
        ExitProcess(1);
    }

    printf("Number of iterations: %d\n", iterations);

    for (int i = 0; i < iterations; i++) {
        printf("Iteration %d, PID: %d\n", i + 1, GetCurrentProcessId());
        Sleep(500);
    }

    ExitProcess(0);
}