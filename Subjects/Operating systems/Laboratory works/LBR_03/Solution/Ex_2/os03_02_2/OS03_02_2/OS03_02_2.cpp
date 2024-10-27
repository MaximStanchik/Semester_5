#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    DWORD processID = GetCurrentProcessId();
    cout << "Process ID: " << processID << endl;

    for (int i = 0; i < 125; i++) {
        Sleep(1000); 
        cout << "Iteration: " << i + 1 << " in Process ID: " << processID << endl;
    }

    return 0;
}