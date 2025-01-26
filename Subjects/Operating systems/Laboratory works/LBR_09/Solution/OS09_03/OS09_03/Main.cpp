#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>

using namespace std;

BOOL insRowFileTxt(LPCWSTR FileName, LPCWSTR str, int row) {
    wifstream file(FileName);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Íå óäàëîñü îòêðûòü ôàéë: " << FileName << endl;
        return FALSE;
    }

    vector<wstring> lines;
    wstring line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (row < -1 || row > static_cast<int>(lines.size())) {
        cerr << "Ñòðîêà " << row << " äëÿ âñòàâêè âûõîäèò çà ïðåäåëû ôàéëà" << endl;
        return FALSE;
    }

    if (row == 0) {
        lines.insert(lines.begin(), str);
    }
    else if (row == -1) {
        lines.push_back(str);
    }
    else {
        lines.insert(lines.begin() + row, str);
    }

    wofstream outFile(FileName);
    outFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    for (const auto& line : lines) {
        outFile << line << endl;
    }
    outFile.close();
    return TRUE;
}

BOOL printFileTxt(LPCWSTR FileName) {
    wifstream file(FileName);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Íå óäàëîñü îòêðûòü ôàéë: " << FileName << endl;
        return FALSE;
    }

    wcout << L"Ñîäåðæèìîå ôàéëà:" << endl;
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

    cout << "Äî âñòàâêè ñòðîê: " << endl;
    printFileTxt(fileName);
    cout << endl;

    insRowFileTxt(fileName, L"ÍÎÂÀß ÑÒÐÎÊÀ Â ÍÀ×ÀËÅ", 0); 
    insRowFileTxt(fileName, L"ÍÎÂÀß ÑÒÐÎÊÀ Â ÊÎÍÖÅ", -1); 
    insRowFileTxt(fileName, L"ÍÎÂÀß ÑÒÐÎÊÀ Â ÏÎÇÈÖÈÞ 5", 5); 
    insRowFileTxt(fileName, L"ÍÎÂÀß ÑÒÐÎÊÀ Â ÏÎÇÈÖÈÞ 7", 7); 

    cout << "Ïîñëå âñòàâêè ñòðîê: " << endl;
    printFileTxt(fileName);
    cout << endl;

    return 0;
}