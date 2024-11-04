#include <stdio.h>
#include <windows.h>

#define MAX_PRIMES 1000

typedef struct {
    int lower;
    int upper;
    int threadId;
} ThreadData;

CRITICAL_SECTION cs; 
int globalPrimes[MAX_PRIMES]; 
int primeCount = 0;
DWORD tlsIndex;

DWORD WINAPI L4Thread(LPVOID param) {
    ThreadData* data = (ThreadData*)param;

    int* localPrimes = (int*)malloc(MAX_PRIMES * sizeof(int));
    if (!localPrimes) {
        fprintf(stderr, "Error allocating memory for localPrimes\n");
        return 1;
    }

    if (!TlsSetValue(tlsIndex, localPrimes)) {
        fprintf(stderr, "Error setting TLS value\n");
        free(localPrimes);
        return 1;
    }

    int localCount = 0;
    for (int i = data->lower; i <= data->upper; i++) {
        if (isPrime(i)) {
            if (localCount < MAX_PRIMES) {
                localPrimes[localCount++] = i;
            }
        }
    }

    EnterCriticalSection(&cs);
    for (int i = 0; i < localCount; i++) {
        if (primeCount < MAX_PRIMES) {
            globalPrimes[primeCount++] = localPrimes[i];
        }
    }
    LeaveCriticalSection(&cs);

    free(localPrimes); 
    return 0;
}


int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        Sleep(1500);
        if (num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <Number of threads> <Lower range> <Upper range>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numberOfThreads = atoi(argv[1]);
    int lower = atoi(argv[2]);
    int upper = atoi(argv[3]);

    if (numberOfThreads < 1 || upper < lower) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    InitializeCriticalSection(&cs);

    tlsIndex = TlsAlloc();
    if (tlsIndex == TLS_OUT_OF_INDEXES) {
        fprintf(stderr, "Error allocating TLS index\n");
        DeleteCriticalSection(&cs);
        return EXIT_FAILURE;
    }

    HANDLE* threads = (HANDLE*)malloc(numberOfThreads * sizeof(HANDLE));
    ThreadData* threadData = (ThreadData*)malloc(numberOfThreads * sizeof(ThreadData));

    if (!threads || !threadData) {
        fprintf(stderr, "Error allocating memory for threads or threadData\n");
        DeleteCriticalSection(&cs);
        TlsFree(tlsIndex);
        if (threads) free(threads);
        if (threadData) free(threadData);
        return EXIT_FAILURE;
    }

    int range = upper - lower + 1;
    int partSize = range / numberOfThreads;
    int remainder = range % numberOfThreads;

    for (int i = 0; i < numberOfThreads; i++) {
        threadData[i].lower = lower + i * partSize + (i < remainder ? i : remainder);
        threadData[i].upper = threadData[i].lower + partSize - 1 + (i < remainder ? 1 : 0);
        threadData[i].threadId = i + 1;

        threads[i] = CreateThread(NULL, 0, L4Thread, &threadData[i], 0, NULL);
        if (threads[i] == NULL) {
            fprintf(stderr, "Error creating thread %d\n", i);
            for (int j = 0; j < i; j++) CloseHandle(threads[j]);
            DeleteCriticalSection(&cs);
            TlsFree(tlsIndex);
            free(threads);
            free(threadData);
            return EXIT_FAILURE;
        }
    }

    WaitForMultipleObjects(numberOfThreads, threads, TRUE, INFINITE);
    for (int i = 0; i < numberOfThreads; i++) {
        CloseHandle(threads[i]);
    }

    free(threads);
    free(threadData);
    TlsFree(tlsIndex);

    for (int i = 0; i < primeCount - 1; i++) {
        for (int j = i + 1; j < primeCount; j++) {
            if (globalPrimes[i] > globalPrimes[j]) {
                int temp = globalPrimes[i];
                globalPrimes[i] = globalPrimes[j];
                globalPrimes[j] = temp;
            }
        }
    }

    printf("Found prime numbers:\n");
    for (int i = 0; i < primeCount; i++) {
        printf("%d ", globalPrimes[i]);
    }
    printf("\n");

    DeleteCriticalSection(&cs);

    return 0;
}