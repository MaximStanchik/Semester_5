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
        wcerr << L"�� ������� ������� ����: " << FileName << endl;
        return FALSE;
    }

    vector<wstring> lines;
    wstring line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (row >= lines.size()) {
        cerr << "������ " << row + 1 << " ��� �������� �� ����������" << endl;
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
        wcerr << L"�� ������� ������� ����: " << FileName << endl;
        return FALSE;
    }

    wcout << L"���������� �����:" << endl;
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

    cout << "�� �������� �����: " << endl;
    printFileTxt(fileName);
    cout << endl;

	cout << "������� ������ 1: " << endl;
    delRowFileTxt(fileName, 1);
    printFileTxt(fileName);
    cout << endl;

	cout << "������� ������ 3: " << endl;
    delRowFileTxt(fileName, 3);
    printFileTxt(fileName);
    cout << endl;

    cout << "������� ������ 8: " << endl;
    delRowFileTxt(fileName, 8);
    printFileTxt(fileName);
    cout << endl;

    cout << "������� ������ 10: " << endl;
    delRowFileTxt(fileName, 10);
    printFileTxt(fileName);
    cout << endl;

    cout << "����� �������� ���� ������ �����: " << endl;
    printFileTxt(fileName);
    cout << endl;

	return 0;
}