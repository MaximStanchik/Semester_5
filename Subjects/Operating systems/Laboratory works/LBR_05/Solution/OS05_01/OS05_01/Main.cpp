#include <iostream>
#include <windows.h>
#include <bitset>

using namespace std;

//Maxim Stanchik
int main() {
    setlocale(LC_ALL, "Rus");

    cout << "Идентификатор текущего процесса: " << GetCurrentProcessId() << endl;
    cout << "Идентификатор текущего потока (main): " << GetCurrentThreadId() << endl;

    HANDLE hProcess = GetCurrentProcess();
    cout << "Приоритет (приоритетный класс) текущего процесса: " << GetPriorityClass(hProcess) << endl;
    cout << "Приоритет текущего потока: " << GetThreadPriority(GetCurrentThread()) << endl;

    DWORD_PTR processAffinityMask, systemAffinityMask;
    if (GetProcessAffinityMask(hProcess, &processAffinityMask, &systemAffinityMask)) {
        cout << "Маска (affinity mask) доступных процессу процессоров в двоичном виде: "
            << bitset<sizeof(DWORD_PTR) * 8>(processAffinityMask) << endl;
    }
    else {
        cerr << "Ошибка при получении маски аффинности процесса: " << GetLastError() << endl;
    }

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    cout << "Количество процессоров, доступных процессу: " << sysInfo.dwNumberOfProcessors << endl;

    DWORD_PTR threadAffinityMask = SetThreadAffinityMask(GetCurrentThread(), processAffinityMask);
    if (threadAffinityMask != 0) {
        cout << "Предыдущая маска аффинности потока: "
            << bitset<sizeof(DWORD_PTR) * 8>(threadAffinityMask) << endl;
    }
    else {
        cerr << "Ошибка при получении маски аффинности потока: " << GetLastError() << endl;
    }

    SetThreadAffinityMask(GetCurrentThread(), threadAffinityMask);
    CloseHandle(hProcess);
    return 0;
}