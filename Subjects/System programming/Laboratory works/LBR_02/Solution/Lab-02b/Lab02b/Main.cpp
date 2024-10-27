#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    const wchar_t* programPath = L"D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorks/LBR_02/Solution/Lab-02xm/Lab-02xm/x64/Debug/Lab-02xm.exe";
    HANDLE hProcesses[3] = { NULL, NULL, NULL };

    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;
    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    wprintf(L"Trying to create first process: %ls\n", programPath);
    if (!CreateProcess(programPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        wprintf(L"Failed to create first process. Error: %d\n", GetLastError());
        return 1;
    }
    else {
        wprintf(L"First child process started with PID: %d\n", pi1.dwProcessId);
        hProcesses[0] = pi1.hProcess;
        CloseHandle(pi1.hThread);
    }

    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;
    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    wchar_t commandLine2[200];
    swprintf_s(commandLine2, sizeof(commandLine2) / sizeof(wchar_t), L"\"%ls\" 5", programPath);
    wprintf(L"Trying to create second process with command line: %ls\n", commandLine2);
    if (!CreateProcess(NULL, commandLine2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        wprintf(L"Failed to create second process. Error: %d\n", GetLastError());
        return 1;
    }
    else {
        wprintf(L"Second child process started with PID: %d\n", pi2.dwProcessId);
        hProcesses[1] = pi2.hProcess;
        CloseHandle(pi2.hThread);
    }

    STARTUPINFO si3;
    PROCESS_INFORMATION pi3;
    ZeroMemory(&si3, sizeof(si3));
    si3.cb = sizeof(si3);
    ZeroMemory(&pi3, sizeof(pi3));

    if (!SetEnvironmentVariable(L"ITER_NUM", L"3")) {
        wprintf(L"Failed to set local environment variable. Error: %d\n", GetLastError());
    }

    wprintf(L"Trying to create third process with NULL as command line.\n");
    if (!CreateProcess(programPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3)) {
        wprintf(L"Failed to create third process. Error: %d\n", GetLastError());
        return 1;
    }
    else {
        wprintf(L"Third child process started with PID: %d\n", pi3.dwProcessId);
        hProcesses[2] = pi3.hProcess;
        CloseHandle(pi3.hThread);
    }

    WaitForMultipleObjects(3, hProcesses, TRUE, INFINITE);

    for (int i = 0; i < 3; i++) {
        if (hProcesses[i] != NULL) {
            CloseHandle(hProcesses[i]);
        }
    }

    wprintf(L"All processes are completed.\n");
    return 0;
}