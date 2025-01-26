#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void printWatchRowFileTxt(LPCWSTR FileName, DWORD mlsec) {
    wifstream file(FileName);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return;
    }

    vector<wstring> previousLines;
    wstring line;

    while (getline(file, line)) {
        previousLines.push_back(line);
    }
    file.close();

    while (true) {
        this_thread::sleep_for(chrono::milliseconds(mlsec));

        file.open(FileName);
        file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

        if (!file.is_open()) {
            wcerr << L"Не удалось открыть файл: " << FileName << endl;
            return;
        }

        vector<wstring> currentLines;
        while (getline(file, line)) {
            currentLines.push_back(line);
        }
        file.close();

        if (currentLines.size() != previousLines.size()) {
            wcerr << L"Изменение количества строк: " << previousLines.size() << L" -> " << currentLines.size() << L" строк." << endl;
        }

        for (size_t i = 0; i < min(previousLines.size(), currentLines.size()); ++i) {
            if (previousLines[i] != currentLines[i]) {
                wcerr << L"Изменение в строке " << i + 1 << L": " << previousLines[i] << L" -> " << currentLines[i] << endl;
            }
        }

        previousLines = currentLines;
    }
}

BOOL printFileTxt(LPCWSTR FileName) {
    wifstream file(FileName);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return FALSE;
    }

    wcout << L"Содержимое файла:" << endl;
    wstring line;
    while (getline(file, line)) {
        wcout << line << endl;
    }

    file.close();
    return TRUE;
}

int main() {
    setlocale(LC_ALL, "Rus");
    LPCWSTR fileName = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_09\\Solution\\file.txt";

    thread watcher(printWatchRowFileTxt, fileName, 2000); 
    watcher.detach(); 

    cout << "Наблюдение за файлом начато. Нажмите Enter для завершения." << endl;
    cin.get(); 

    return 0;
}