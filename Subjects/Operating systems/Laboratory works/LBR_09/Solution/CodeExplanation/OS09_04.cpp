#include <iostream> // Подключаем библиотеку для ввода/вывода
#include <Windows.h> // Подключаем Windows API
#include <string> // Подключаем библиотеку для работы со строками
#include <fstream> // Подключаем библиотеку для работы с файлами
#include <locale> // Подключаем библиотеку для локализации
#include <codecvt> // Подключаем библиотеку для конвертации кодировок
#include <vector> // Подключаем библиотеку для работы с векторами
#include <thread> // Подключаем библиотеку для работы с потоками
#include <chrono> // Подключаем библиотеку для работы со временем

using namespace std;

void printWatchRowFileTxt(LPCWSTR FileName, DWORD mlsec) {
    wifstream file(FileName); // открываем файл для чтения
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // устанавливаем UTF-8

    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл: " << FileName << endl;
        return;
    }

    vector<wstring> previousLines; // вектор предыдущих строк
    wstring line; // переменная для текущей строки

    while (getline(file, line)) { //считываем строки из файла и сохраняем в вектор
        previousLines.push_back(line);
    }
    file.close(); // закрываем файл после чтения

    while (true) {
        this_thread::sleep_for(chrono::milliseconds(mlsec));

        file.open(FileName); // открываем файл для чтения
        file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // устанавливаем кодировку UTF-8

        if (!file.is_open()) {
            wcerr << L"Не удалось открыть файл: " << FileName << endl;
            return;
        }

        vector<wstring> currentLines; // ввектор для хранения текущих строк
        while (getline(file, line)) { // считываем строки из файла
            currentLines.push_back(line); // добавляем каждую считанную строку
        }
        file.close(); // закрываем файл после чтения

        if (currentLines.size() != previousLines.size()) { // проверяем изменилось ли кол-во строк
            wcerr << L"Изменение количества строк: " << previousLines.size() << L" -> " << currentLines.size() << L" строк." << endl;
        }

        // сравниваем строки из предыдущей и текущей версий файла
        for (size_t i = 0; i < min(previousLines.size(), currentLines.size()); ++i) {
            if (previousLines[i] != currentLines[i]) { // если строки отличаются
                wcerr << L"Изменение в строке " << i + 1 << L": " << previousLines[i] << L" -> " << currentLines[i] << endl; // сообщение об изменении
            }
        }

        previousLines = currentLines; // обновляем предыдущие строки на текущие
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

    // Создаем и запускаем поток для наблюдения за изменениями в файле
    thread watcher(printWatchRowFileTxt, fileName, 2000);
    watcher.detach(); // Отделяем поток, чтобы он работал независимо

    cout << "Наблюдение за файлом начато. Нажмите Enter для завершения." << endl; // Сообщение о начале наблюдения
    cin.get(); // Ожидаем ввода от пользователя

    return 0;
}