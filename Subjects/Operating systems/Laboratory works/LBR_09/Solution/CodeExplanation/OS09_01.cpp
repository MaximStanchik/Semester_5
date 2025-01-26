#include <iostream>
#include <Windows.h> // Подключаем Windows API
#include <string> 
#include <fstream> // Подключаем библиотеку для работы с файлами
#include <locale> // Подключаем библиотеку для локализации
#include <codecvt> // Подключаем библиотеку для конвертации кодировок

using namespace std;

LPCWSTR getFileType(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN: {
        return L"Тип файла не определен";
    }

    case FILE_TYPE_DISK: {
        return L"Файл находится на диске";
    }

    case FILE_TYPE_CHAR: {
        return L"Файл является символьным устройством";
    }

    case FILE_TYPE_PIPE: {
        return L"Файл представляет собой именнованный или анонимный канал";
    }

    case FILE_TYPE_REMOTE: {
        return L"Файл является удаленным";
    }

    default: {
        return L"Неизвестный тип файла";
    }
    }
}


BOOL printFileInfo(LPCWSTR FileName) {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo; // Структура для хранения информации о файле

    if (!GetFileAttributesEx(FileName, GetFileExInfoStandard, &fileInfo)) { // получение атрибутов файла
        wcerr << L"Ошибка получения информации о файле: " << FileName << endl; // сообщение об ошибке
        return FALSE;
    }

    LARGE_INTEGER fileSize; // переменная для хранения размера файла
    fileSize.LowPart = fileInfo.nFileSizeLow; // низкая часть размера файла
    fileSize.HighPart = fileInfo.nFileSizeHigh; // высокая часть размера файла

    SYSTEMTIME creationTime, lastWriteTime; // переменные для хранения времени создания последнего обновления
    FileTimeToSystemTime(&fileInfo.ftCreationTime, &creationTime); // конвертируем время создания в системное время
    FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &lastWriteTime); // конвертируем время последнего обновления

    HANDLE hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // открываем файл для чтения
    if (hFile == INVALID_HANDLE_VALUE) { // проверяем удалось ли открыть файл
        wcerr << L"Ошибка открытия файла: " << FileName << endl;
        return FALSE;
    }

    // вывод информации о файле
    wcout << L"Имя файла: " << FileName << endl;
    wcout << L"Тип файла: " << getFileType(hFile) << endl;
    wcout << L"Размер файла: " << fileSize.QuadPart << L" байт" << endl;
    wcout << L"Дата и время создания: " << creationTime.wDay << L"." << creationTime.wMonth << L"." << creationTime.wYear << L" "
        << creationTime.wHour << L":" << creationTime.wMinute << L":" << creationTime.wSecond << endl;
    wcout << L"Дата и время последнего обновления: " << lastWriteTime.wDay << L"." << lastWriteTime.wMonth << L"." << lastWriteTime.wYear << L" "
        << lastWriteTime.wHour << L":" << lastWriteTime.wMinute << L":" << lastWriteTime.wSecond << endl;

    return TRUE; // успешное завершение функции
}


BOOL printFileTxt(LPCWSTR FileName) {
    wifstream file(FileName); // открываем файл как широкий ввод-вывод
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // устанавливаем кодировку UTF-8

    if (!file.is_open()) {
        wcerr << L"!!!Ошибка!!! Файл не открылся: " << FileName << endl; // сообщение об ошибке
        return FALSE;
    }

    wcout << L"Содержимое файла:" << endl;
    wstring line; // переменная для хранения строки
    while (getline(file, line)) { // читаем файл построчно
        wcout << line << endl;
    }

    file.close(); // закрываем файл
    return TRUE;
}

int main() {
    setlocale(LC_ALL, "Rus");
    LPCWSTR fileName = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_09\\Solution\\file.txt"; 
    printFileInfo(fileName);
	printFileTxt(fileName);

    return 0;
}