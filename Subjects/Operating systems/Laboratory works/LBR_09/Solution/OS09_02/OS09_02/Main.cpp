#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>

using namespace std;

BOOL delRowFileTxt(LPCWSTR FileName, DWORD row) {
    row = row - 1;
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

    if (row >= lines.size()) {
        cerr << "Строка " << row + 1 << " для удаления не существует" << endl;
        return FALSE;
    }

    lines.erase(lines.begin() + row);

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

	cout << "Удалили строку 1: " << endl;
    delRowFileTxt(fileName, 1);
    printFileTxt(fileName);
    cout << endl;

	cout << "Удалили строку 3: " << endl;
    delRowFileTxt(fileName, 3);
    printFileTxt(fileName);
    cout << endl;

    cout << "Удалили строку 8: " << endl;
    delRowFileTxt(fileName, 8);
    printFileTxt(fileName);
    cout << endl;

    cout << "Удалили строку 10: " << endl;
    delRowFileTxt(fileName, 10);
    printFileTxt(fileName);
    cout << endl;

    cout << "После удаления всех нужных строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

	return 0;
}