#include <stdio.h> // подключение библиотеки для ввода-вывода
#include <stdlib.h> // подключение библиотеки для работы с функциями общего назначения
#include <windows.h> // подключение библиотеки Windows API

#define BUFFER_SIZE 1024 // определение размера буфера для получения изменений директории

BOOL DirectoryExists(LPCSTR dirPath) {
    DWORD fileAttr = GetFileAttributesA(dirPath); // получение атрибутов файла по заданному пути
    return (fileAttr != INVALID_FILE_ATTRIBUTES && (fileAttr & FILE_ATTRIBUTE_DIRECTORY)); // проверка, существует ли директория
}

void ListDirectoryContents(const char* directory) {
    char searchPath[MAX_PATH]; // объявление строки для хранения пути поиска
    snprintf(searchPath, sizeof(searchPath), "%s\\*", directory); // форматирование строки поиска, добавление символва *

    WIN32_FIND_DATA findFileData; // структура для хранения информации о найденном файле
    HANDLE hFind = FindFirstFileA(searchPath, &findFileData); // поиск первого файла в директории

    if (hFind == INVALID_HANDLE_VALUE) { // проверка на успешное открытие директории
        printf("Error: Failed to open directory %s. Perhaps he doesn't exist.\n", directory); // сообщение об ошибке
        return; // завершение функции
    }
     
    printf("Catalog contents %s:\n", directory); // вывод информации о содержимом директории
    do {
        const char* fileName = findFileData.cFileName; // получение имени файла

        if (strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0) { // игнорирование текущей и родительской директории
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // проверка, является ли элемент директорией
                printf("[Directory] %s\n", fileName); // вывод имени директории
            }
            else {
                printf("[File] %s\n", fileName); // вывод имени файла
            }
        }
    } 
    while (FindNextFileA(hFind, &findFileData) != 0); // цикл для получения следующего файла

    FindClose(hFind); // закрытие дескриптора поиска
}

void MonitorDirectory(LPCSTR dirPath) {
    HANDLE hDir = CreateFileA( // открытие директории для мониторинга 
        dirPath,
        FILE_LIST_DIRECTORY, // указание, что мы хотим получать события для этой директории
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // разрешение на совместный доступ
        NULL,
        OPEN_EXISTING, // открытие существующей директории
        FILE_FLAG_BACKUP_SEMANTICS, // флаг для правильной работы с директориями
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) { // проверка на успешность открытия директории
        printf("Failed to open directory for monitoring: %s\n", dirPath); // сообщение об ошибке
        return; // завершение функции
    }

    printf("Start monitoring changes in the directory: '%s'\n", dirPath); // подтверждение начала мониторинга

    char buffer[BUFFER_SIZE]; // буфер для хранения информации об изменениях
    DWORD bytesReturned; // переменная для хранения количества байтов, возвращенных функцией

    while (TRUE) { // бесконечный цикл для мониторинга изменений
        if (ReadDirectoryChangesW( // чтение изменений в директории
            hDir, 
            buffer,
            BUFFER_SIZE,
            TRUE, // указание на мониторинг поддиректорий
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE |
            FILE_NOTIFY_CHANGE_LAST_WRITE, // указание типов изменений, которые мы хотим отслеживать
            &bytesReturned, // получение количества байтов
            NULL,
            NULL
        )) {
            FILE_NOTIFY_INFORMATION* pNotify = (FILE_NOTIFY_INFORMATION*)buffer; // приведение буфера к нужному типу

            do {
                char fileName[MAX_PATH]; // буфер для имени файла
                int nameLength = WideCharToMultiByte(CP_UTF8, 0, pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR), fileName, MAX_PATH, NULL, NULL); // преобразование имени файла из WCHAR в UTF-8
                fileName[nameLength] = '\0'; // завершение строки

                switch (pNotify->Action) { // обработка типа действия
                case FILE_ACTION_ADDED: // если файл был добавлен
                    printf("Created: %s\n", fileName); // вывод сообщения об удалении
                    break;
                case FILE_ACTION_REMOVED: // если файл был удален
                    printf("Deleted: %s\n", fileName);
                    break; 
                case FILE_ACTION_MODIFIED: // если файл был изменен
                    printf("Changed: %s\n", fileName);
                    break;
                case FILE_ACTION_RENAMED_OLD_NAME: // если файл был переименован (старое имя)
                    printf("Renamed (old name): %s\n", fileName);
                    break;
                case FILE_ACTION_RENAMED_NEW_NAME: // если файл был переименован (новое имя)
                    printf("Renamed (new name): %s\n", fileName);
                    break;
                default:
                    printf("Unknown action: %s\n", fileName);
                    break;
                }

                if (pNotify->NextEntryOffset == 0) break; // если больше нет записей, выход из цикла
                pNotify = (FILE_NOTIFY_INFORMATION*)((char*)pNotify + pNotify->NextEntryOffset); // переход к следующей записи
            } while (TRUE);
        }
        else {
            printf("Error reading directory changes\n");
            break;
        }
    }

    CloseHandle(hDir); // закрытие дескриптора директории
}

int main(int argc, char* argv[]) {
    if (argc != 2) { // проверка кол-ва аргументов командной строки
        printf("Usage: %s <directory path>\n", argv[0]);
        return 1;
    }

    char* dirPath = argv[1];

    if (!DirectoryExists(dirPath)) { // проверка существования директории
        printf("Error: Directory does not exist: %s\n", dirPath);
        return 1;
    }
    ListDirectoryContents(dirPath); // вывод содержимого директории
    MonitorDirectory(dirPath);  // начало мониторинга директории

    return 0; // завершение программы
}


ReadDirectoryChangesW(
hDir,                     // Дескриптор директории, которую нужно мониторить
buffer,                   // Указатель на буфер, в который будут записаны изменения
BUFFER_SIZE,              // Размер буфера в байтах
TRUE,                     // Указывает, нужно ли мониторить изменения в поддиректориях (TRUE - да)
FILE_NOTIFY_CHANGE_FILE_NAME |
FILE_NOTIFY_CHANGE_DIR_NAME |
FILE_NOTIFY_CHANGE_ATTRIBUTES |
FILE_NOTIFY_CHANGE_SIZE |
FILE_NOTIFY_CHANGE_LAST_WRITE, // Указывает, какие изменения нужно отслеживать
& bytesReturned,           // Указатель на переменную, в которую будет записано количество байтов, записанных в буфер
NULL,                     // Указатель на структуру OVERLAPPED (можно использовать для асинхронного ввода-вывода)
NULL                      // Указатель на функцию, которая будет вызвана при завершении операции (если используется асинхронный ввод-вывод)
);