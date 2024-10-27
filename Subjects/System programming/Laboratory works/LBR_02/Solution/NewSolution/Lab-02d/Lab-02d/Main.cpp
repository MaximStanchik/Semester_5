#include <iostream>
#include <windows.h>
#include <conio.h> 

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    wchar_t Lab02inf_path[] = L"D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorks/LBR_02/Solution/NewSolution/Lab-02inf/Lab-02inf/x64/Debug/Lab-02inf.exe";

    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo)); 
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    if (!CreateProcess(Lab02inf_path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        cout << "Ошибка при создании процесса: " << GetLastError() << endl;
        return 1; 
    }

    cout << "Lab-02inf запущен с PID: " << processInfo.dwProcessId << endl;

    cout << "Нажмите любую клавишу для завершения Lab-02inf аварийным образом..." << endl;

    while (!_kbhit()); 
    _getch(); 

    TerminateProcess(processInfo.hProcess, 0);
    cout << "Lab-02inf завершен аварийным образом." << endl;

    cout << "PID дочернего процесса: " << processInfo.dwProcessId << endl;

    cout << "Нажмите любую клавишу для выхода..." << endl;
    while (!_kbhit()); 
    _getch(); 

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return 0;
}