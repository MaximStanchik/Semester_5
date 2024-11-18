#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    const wchar_t* path = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_07\\Solution\\OS07_04\\OS07_04\\x64\\Debug\\OS07_04X.exe";
    PROCESS_INFORMATION pi[2];
    STARTUPINFO si[2];

    for (int i = 0; i < 2; ++i) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));
    }

    if (!CreateProcess(path, (LPWSTR)L"OS07_04X.exe 2000", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[0], &pi[0])) {
        cout << "Ошибка создания первого процесса. Код ошибки: " << GetLastError() << endl;
        return 1;
    }

    if (!CreateProcess(path, (LPWSTR)L"OS07_04X.exe 5000", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[1], &pi[1])) {
        cout << "Ошибка создания второго процесса. Код ошибки: " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(pi[0].hProcess, INFINITE);
    WaitForSingleObject(pi[1].hProcess, INFINITE);

    CloseHandle(pi[0].hProcess);
    CloseHandle(pi[0].hThread);
    CloseHandle(pi[1].hProcess);
    CloseHandle(pi[1].hThread);

    return 0;
}