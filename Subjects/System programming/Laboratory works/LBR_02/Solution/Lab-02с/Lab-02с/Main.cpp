#include <stdio.h>
#include <windows.h>

int main() {
    const wchar_t* newDirectory = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\SystemProgramming\\LaboratoryWorks\\LBR_02\\Solution\\Lab-02ñ\\Lab-02ñ"; 
    if (!SetCurrentDirectory(newDirectory)) {
        wprintf(L"Failed to set current directory. Error: %d\n", GetLastError());
        return 1;
    }

    const wchar_t* programName = L"Lab-02hw.exe"; 
    HANDLE hProcesses[5] = { NULL, NULL, NULL, NULL, NULL };

    for (int i = 0; i < 5; i++) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        wchar_t commandLine[100];
        swprintf_s(commandLine, sizeof(commandLine) / sizeof(wchar_t), L"%s", programName);

        wprintf(L"Trying to create process %d with command line: %s\n", i + 1, commandLine);
        if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            wprintf(L"Failed to create process %d. Error: %d\n", i + 1, GetLastError());
            return 1;
        }
        else {
            wprintf(L"Process %d started with PID: %d\n", i + 1, pi.dwProcessId);
            hProcesses[i] = pi.hProcess; 
            CloseHandle(pi.hThread);
        }
    }

    WaitForMultipleObjects(5, hProcesses, TRUE, INFINITE);

    for (int i = 0; i < 5; i++) {
        if (hProcesses[i] != NULL) {
            CloseHandle(hProcesses[i]);
        }
    }

    wprintf(L"All processes are completed.\n");
    return 0;
}