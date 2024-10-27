#include <iostream>
#include <windows.h>
#include <bitset>

using namespace std;

//Maxim Stanchik
int main() {
    setlocale(LC_ALL, "Rus");

    cout << "������������� �������� ��������: " << GetCurrentProcessId() << endl;
    cout << "������������� �������� ������ (main): " << GetCurrentThreadId() << endl;

    HANDLE hProcess = GetCurrentProcess();
    cout << "��������� (������������ �����) �������� ��������: " << GetPriorityClass(hProcess) << endl;
    cout << "��������� �������� ������: " << GetThreadPriority(GetCurrentThread()) << endl;

    DWORD_PTR processAffinityMask, systemAffinityMask;
    if (GetProcessAffinityMask(hProcess, &processAffinityMask, &systemAffinityMask)) {
        cout << "����� (affinity mask) ��������� �������� ����������� � �������� ����: "
            << bitset<sizeof(DWORD_PTR) * 8>(processAffinityMask) << endl;
    }
    else {
        cerr << "������ ��� ��������� ����� ���������� ��������: " << GetLastError() << endl;
    }

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    cout << "���������� �����������, ��������� ��������: " << sysInfo.dwNumberOfProcessors << endl;

    DWORD_PTR threadAffinityMask = SetThreadAffinityMask(GetCurrentThread(), processAffinityMask);
    if (threadAffinityMask != 0) {
        cout << "���������� ����� ���������� ������: "
            << bitset<sizeof(DWORD_PTR) * 8>(threadAffinityMask) << endl;
    }
    else {
        cerr << "������ ��� ��������� ����� ���������� ������: " << GetLastError() << endl;
    }

    SetThreadAffinityMask(GetCurrentThread(), threadAffinityMask);
    CloseHandle(hProcess);
    return 0;
}