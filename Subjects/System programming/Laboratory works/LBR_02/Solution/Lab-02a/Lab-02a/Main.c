#include <stdio.h>
#include <windows.h>

int main() {
    const char* programPath = "D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorks/LBR_02/Solution/Lab-02x/Lab-02x/x64/Debug/Lab-02x.exe";
    HANDLE hProcesses[3] = { NULL, NULL, NULL };

    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;
    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    printf("Trying to create first process: %s\n", programPath);
    if (!CreateProcess(programPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        printf("Failed to create first process. Error: %d\n", GetLastError());
        return 1;
    }
    else {
        printf("First child process started with PID: %d\n", pi1.dwProcessId);
        hProcesses[0] = pi1.hProcess;
        CloseHandle(pi1.hThread);
    }

    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;
    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    char commandLine2[200];
    sprintf_s(commandLine2, sizeof(commandLine2), "\"%s\" 5", programPath); 
    printf("Trying to create second process with command line: %s\n", commandLine2);
    if (!CreateProcess(NULL, commandLine2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        printf("Failed to create second process. Error: %d\n", GetLastError());
        return 1;
    }
    else {
        printf("Second child process started with PID: %d\n", pi2.dwProcessId);
        hProcesses[1] = pi2.hProcess;
        CloseHandle(pi2.hThread);
    }

    STARTUPINFO si3;
    PROCESS_INFORMATION pi3;
    ZeroMemory(&si3, sizeof(si3));
    si3.cb = sizeof(si3);
    ZeroMemory(&pi3, sizeof(pi3));

    char commandLine3[200];
    sprintf_s(commandLine3, sizeof(commandLine3), "\"%s\" 10", programPath); 
    printf("Trying to create third process with command line: %s\n", commandLine3);
    if (!CreateProcess(programPath, commandLine3, NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3)) {
        printf("Failed to create third process. Error: %d\n", GetLastError());
        return 1;
    }
    else {
        printf("Third child process started with PID: %d\n", pi3.dwProcessId);
        hProcesses[2] = pi3.hProcess;
        CloseHandle(pi3.hThread);
    }

    WaitForMultipleObjects(3, hProcesses, TRUE, INFINITE);

    for (int i = 0; i < 3; i++) {
        if (hProcesses[i] != NULL) {
            CloseHandle(hProcesses[i]);
        }
    }

    printf("All processes are completed.\n");
    return 0;
}