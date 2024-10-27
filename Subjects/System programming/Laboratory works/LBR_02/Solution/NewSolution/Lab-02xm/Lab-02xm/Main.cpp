#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    int iterations = 0;

    SetEnvironmentVariable(L"ITER_NUM", L"5");

    if (argc > 1) {
        iterations = atoi(argv[1]);
    }
    else {
        wchar_t buffer[256];
        DWORD result = GetEnvironmentVariable(L"ITER_NUM", buffer, sizeof(buffer) / sizeof(wchar_t));

        if (result > 0) {
            iterations = _wtoi(buffer);
        }
        else {
            cout << " оличество итераций не задано и переменна€ окружени€ ITER_NUM не установлена." << endl;
            ExitProcess(1);
        }
    }

    if (iterations <= 0) {
        cout << " оличество итераций должно быть позитивным числом" << endl;
        ExitProcess(1); 
    }

    cout << " оличество итераций: " << iterations << endl;

    for (int i = 0; i < iterations; i++) {
        Sleep(500);
        cout << "»тераци€ " << i << ", PID: " << GetCurrentProcessId() << " ." << endl;
    }

    ExitProcess(0);
    return 0;
}