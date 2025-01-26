#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt> // Подключаем библиотеку для конвертации кодировок
#include <vector> // Подключаем библиотеку для работы с векторами

using namespace std;

BOOL insRowFileTxt(LPCWSTR FileName, LPCWSTR str, int row) {
    wifstream file(FileName); // Открываем файл для чтения
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8

    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return FALSE;
    }

    vector<wstring> lines; // Вектор для хранения строк файла
    wstring line; // Переменная для текущей строки
    while (getline(file, line)) { // Читаем файл построчно
        lines.push_back(line); // Добавляем каждую строку в вектор
    }
    file.close(); // Закрываем файл после чтения

    // Проверяем, допустим ли индекс строки для вставки
    if (row < -1 || row > static_cast<int>(lines.size())) {
        cerr << "Строка " << row << " для вставки выходит за пределы файла" << endl; // Сообщение об ошибке
        return FALSE; // Возвращаем FALSE при ошибке
    }

    // Вставляем строку в нужную позицию
    if (row == 0) {
        lines.insert(lines.begin(), str); // Вставляем в начало
    }
    else if (row == -1) {
        lines.push_back(str); // Вставляем в конец
    }
    else {
        lines.insert(lines.begin() + row, str); // Вставляем в указанную позицию
    }

    wofstream outFile(FileName); // Открываем файл для записи
    outFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8
    for (const auto& line : lines) { // Проходим по всем строкам в векторе
        outFile << line << endl; // Записываем каждую строку в файл
    }
    outFile.close(); // Закрываем файл после записи
    return TRUE; // Успешное завершение функции
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

    cout << "До вставки строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

    insRowFileTxt(fileName, L"НОВАЯ СТРОКА В НАЧАЛЕ", 0); 
    insRowFileTxt(fileName, L"НОВАЯ СТРОКА В КОНЦЕ", -1); 
    insRowFileTxt(fileName, L"НОВАЯ СТРОКА В ПОЗИЦИЮ 5", 5); 
    insRowFileTxt(fileName, L"НОВАЯ СТРОКА В ПОЗИЦИЮ 7", 7); 

    cout << "После вставки строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

    return 0;
}