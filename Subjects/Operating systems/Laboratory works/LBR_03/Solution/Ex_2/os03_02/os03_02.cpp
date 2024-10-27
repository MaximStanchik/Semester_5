#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    const wchar_t* processName1 = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_03\\Solution\\Ex_2\\os03_02_1\\os03_02_1\\x64\\Debug\\os03_02_1.exe";
    const wchar_t* processName2 = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_03\\Solution\\Ex_2\\os03_02_2\\OS03_02_2\\x64\\Debug\\OS03_02_2.exe";

    PROCESS_INFORMATION processInfo1, processInfo2;
    ZeroMemory(&processInfo1, sizeof(processInfo1));
    ZeroMemory(&processInfo2, sizeof(processInfo2));

    STARTUPINFO startupInfo1, startupInfo2;
    ZeroMemory(&startupInfo1, sizeof(startupInfo1));
    startupInfo1.cb = sizeof(startupInfo1);
    ZeroMemory(&startupInfo2, sizeof(startupInfo2));
    startupInfo2.cb = sizeof(startupInfo2);

    if (!CreateProcess(processName1, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo1, &processInfo1)) {
        cerr << "Failed to create process 1: " << GetLastError() << endl;
        return 1;
    }

    if (!CreateProcess(processName2, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo2, &processInfo2)) {
        cerr << "Failed to create process 2: " << GetLastError() << endl;
        return 1;
    }

    CloseHandle(processInfo1.hProcess);
    CloseHandle(processInfo1.hThread);
    CloseHandle(processInfo2.hProcess);
    CloseHandle(processInfo2.hThread);

    for (int i = 0; i < 100; i++) {
        Sleep(1000);
        cout << i << endl;
    }

    return 0;
}