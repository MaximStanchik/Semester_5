#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    const wchar_t* newDir = L"D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorks/LBR_02/Solution/NewSolution/Lab-02c-catalog";
    if (!SetCurrentDirectory(newDir)) {
        wcout << L"Не удалось установить текущий каталог: " << GetLastError() << endl;
        return 1;
    }

    const wchar_t* appName = L"Lab-02hw.exe";
    wstring paths[5];
    paths[0] = L"D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorks/LBR_02/Solution/NewSolution/Lab-02c-catalog/Lab-02hw-1.exe";
    paths[1] = L"D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorks/LBR_02/Solution/NewSolution/Lab-02c/Lab-02c/Lab-02hw-2.exe";

    wchar_t systemDir[MAX_PATH];
    wchar_t windowsDir[MAX_PATH];
    GetSystemDirectory(systemDir, MAX_PATH);
    GetWindowsDirectory(windowsDir, MAX_PATH);
    paths[2] = wstring(systemDir) + L"\\Lab-02hw-3.exe";
    paths[3] = wstring(windowsDir) + L"\\Lab-02hw-4.exe";

    wchar_t path[MAX_PATH * 10]; 
    DWORD result = GetEnvironmentVariable(L"PATH", path, MAX_PATH * 10);

    if (result == 0) {
        wcout << L"Ошибка при получении переменной PATH: " << GetLastError() << endl;
        return 1;
    }

    wchar_t* token;
    wchar_t* context = nullptr;
    token = wcstok_s(path, L";", &context);

    bool foundLab02hw5 = false;
    while (token != NULL) {

        wstring fullPath = wstring(token) + L"\\Lab-02hw-5.exe";

        if (GetFileAttributes(fullPath.c_str()) != INVALID_FILE_ATTRIBUTES) {
            paths[4] = fullPath;
            foundLab02hw5 = true;
            break;
        }

        token = wcstok_s(NULL, L";", &context);
    }

    if (!foundLab02hw5) {
        wcout << L"Не удалось найти Lab-02hw-5.exe в переменной PATH." << endl;
        return 1;
    }

    PROCESS_INFORMATION processInfo[5];
    STARTUPINFO startupInfo[5];

    for (int i = 0; i < 5; i++) {
        ZeroMemory(&startupInfo[i], sizeof(startupInfo[i]));
        startupInfo[i].cb = sizeof(startupInfo[i]);
        ZeroMemory(&processInfo[i], sizeof(processInfo[i]));

        if (!CreateProcess(paths[i].c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo[i], &processInfo[i])) {
            wcout << L"Ошибка при создании процесса " << i + 1 << L": " << GetLastError() << endl;
            return 1;
        }
        wcout << L"Процесс " << i + 1 << L" запущен с PID: " << processInfo[i].dwProcessId << endl;
    }

    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(processInfo[i].hProcess, INFINITE);
        CloseHandle(processInfo[i].hProcess);
        CloseHandle(processInfo[i].hThread);
    }

    wcout << L"Все процессы завершены." << endl;
    return 0;
}
