#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        printf("There should be four parameters in total on the command line. The fifth parameter (mutex name) is optional\n");
        return 1;
    }

    int num_processes = atoi(argv[1]);
    int startOfRangeValue = atoi(argv[2]);
    int endOfRangeValue = atoi(argv[3]);
    const char* mutexName;
    if (argc == 5) {
        mutexName = argv[4];
    }
    else {
        mutexName = "DefaultMutex";
    }

    if (num_processes <= 0) {
        printf("Please provide a positive number of processes.\n");
        return 1;
    }

    HANDLE hMutex = CreateMutex(NULL, FALSE, mutexName);
    if (hMutex == NULL) {
        printf("CreateMutex failed (%d).\n", GetLastError());
        return 1;
    }

    PROCESS_INFORMATION* pinfo = (PROCESS_INFORMATION*)malloc(num_processes * sizeof(PROCESS_INFORMATION));
    STARTUPINFO* sinfo = (STARTUPINFO*)malloc(num_processes * sizeof(STARTUPINFO));

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    HANDLE hReadPipe, hWritePipe;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        printf("CreatePipe failed (%d).\n", GetLastError());
        CloseHandle(hMutex);
        free(pinfo);
        free(sinfo);
        return 1;
    }

    const char* executablePath = "D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\SystemProgramming\\LaboratoryWorks\\LBR_03\\Solution\\Lab-03a-client\\x64\\Debug\\Lab-03a-client.exe";

    for (int i = 0; i < num_processes; ++i) {
        ZeroMemory(&sinfo[i], sizeof(sinfo[i]));
        sinfo[i].cb = sizeof(sinfo[i]);
        ZeroMemory(&pinfo[i], sizeof(pinfo[i]));

        // Указываем дескрипторы каналов
        sinfo[i].hStdOutput = hWritePipe;
        sinfo[i].hStdError = hWritePipe;
        sinfo[i].dwFlags |= STARTF_USESTDHANDLES;

        // Вычисляем границы диапазона для каждого процесса
        int rangeSize = (endOfRangeValue - startOfRangeValue) / num_processes;
        int lowerBound = startOfRangeValue + i * rangeSize;
        int upperBound = (i == num_processes - 1) ? endOfRangeValue : lowerBound + rangeSize;

        // Формируем строку аргументов
        char fullArgs[256];
        sprintf_s(fullArgs, sizeof(fullArgs), "%d %d %s", lowerBound, upperBound, mutexName);

        // Запускаем процесс клиента
        if (!CreateProcess(executablePath, fullArgs, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo[i], &pinfo[i])) {
            printf("CreateProcess failed (%d).\n", GetLastError());
            CloseHandle(hWritePipe);
            CloseHandle(hReadPipe);
            CloseHandle(hMutex);
            free(pinfo);
            free(sinfo);
            return 1;
        }
    }

    // Закрытие дескриптора записи после запуска процессов
    CloseHandle(hWritePipe);

    // Чтение данных от дочерних процессов
    int primeNumber;
    DWORD bytesRead;
    while (ReadFile(hReadPipe, &primeNumber, sizeof(int), &bytesRead, NULL) && bytesRead > 0) {
        printf("Found prime number: %d\n", primeNumber);
    }

    // Ожидание завершения всех процессов
    for (int i = 0; i < num_processes; ++i) {
        WaitForSingleObject(pinfo[i].hProcess, INFINITE);
        CloseHandle(pinfo[i].hProcess);
        CloseHandle(pinfo[i].hThread);
    }

    // Закрытие дескрипторов
    CloseHandle(hReadPipe);
    CloseHandle(hMutex);
    free(pinfo);
    free(sinfo);
    return 0;
}
