#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <algorithm>

using namespace std;

BOOL delRowFileTxt(LPCWSTR FileName, const vector<DWORD>& rowsToDelete) {
    wifstream file(FileName);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return FALSE;
    }

    vector<wstring> lines;
    wstring line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    vector<DWORD> sortedRows = rowsToDelete;
    sort(sortedRows.rbegin(), sortedRows.rend());

    for (DWORD row : sortedRows) {
        if (row > 0) {
            row--;
        }
        if (row >= lines.size()) {
            cerr << "Строка " << row + 1 << " для удаления не существует" << endl;
            continue;
        }
        lines.erase(lines.begin() + row);
    }

    wofstream outFile(FileName);
    outFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    for (const auto& str : lines) {
        outFile << str << endl;
    }
    outFile.close();
    return TRUE;
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

    cout << "До удаления строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

    vector<DWORD> rowsToDelete = { 1, 3, 8, 10 };

    delRowFileTxt(fileName, rowsToDelete);

    cout << "После удаления строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

    return 0;
}