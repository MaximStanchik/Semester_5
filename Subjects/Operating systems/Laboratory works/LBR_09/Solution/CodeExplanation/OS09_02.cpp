#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream> // Подключаем библиотеку для работы с файлами
#include <locale> // Подключаем библиотеку для локализации
#include <codecvt> // Подключаем библиотеку для конвертации кодировок
#include <vector>

using namespace std;

// Функция для удаления строки из текстового файла
BOOL delRowFileTxt(LPCWSTR FileName, DWORD row) {
    wifstream file(FileName); // Открываем файл для чтения
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8

    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return FALSE;
    }

    vector<wstring> lines; // Вектор для хранения строк файла
    wstring line; // Переменная для текущей строки
    while (getline(file, line)) { // Читаем файл построчно
        lines.push_back(line); // Добавляем каждую строку в вектор
    }
    file.close(); // Закрываем файл

    // Проверяем, существует ли строка для удаления
    if (row >= lines.size()) {
        cerr << "Строка " << row << " для удаления не существует" << endl; // Сообщение об ошибке
        return FALSE; // Возвращаем FALSE при ошибке
    }

    lines.erase(lines.begin() + row); // Удаляем строку по указанному индексу

    wofstream outFile(FileName);  // Открываем файл для записи
    outFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8
    for (const auto& str : lines) { // Проходим по оставшимся строкам
        outFile << str << endl; // Записываем каждую строку в файл
    }
    outFile.close(); // Закрываем файл
    return TRUE;
}

BOOL printFileTxt(LPCWSTR FileName) {
    wifstream file(FileName); // Открываем файл для чтения
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8

    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return FALSE;
    }

    wcout << L"Содержимое файла:" << endl;
    wstring line;
    while (getline(file, line)) {
        wcout << line << endl;
    }

    file.close(); // Закрываем файл
    return TRUE;
}

int main() {
	setlocale(LC_ALL, "Rus");
    LPCWSTR fileName = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_09\\Solution\\file.txt";

    cout << "До удаления строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

    delRowFileTxt(fileName, 1);
    delRowFileTxt(fileName, 3);
    delRowFileTxt(fileName, 8);
    delRowFileTxt(fileName, 10);

    cout << "После удаления строк: " << endl;
    printFileTxt(fileName);
    cout << endl;

	return 0;
}