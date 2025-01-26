#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 1024

BOOL DirectoryExists(LPCSTR dirPath) {
    DWORD fileAttr = GetFileAttributesA(dirPath);
    return (fileAttr != INVALID_FILE_ATTRIBUTES && (fileAttr & FILE_ATTRIBUTE_DIRECTORY));
}

void ListDirectoryContents(const char* directory) {
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", directory); 

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFileA(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error: Failed to open directory %s. Perhaps he doesn't exist.\n", directory);
        return;
    }

    printf("Catalog contents %s:\n", directory);
    do {
        const char* fileName = findFileData.cFileName;

        if (strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0) {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("[Directory] %s\n", fileName);
            }
            else {
                printf("[File] %s\n", fileName);
            }
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void MonitorDirectory(LPCSTR dirPath) {
    HANDLE hDir = CreateFileA(
        dirPath,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        printf("Failed to open directory for monitoring: %s\n", dirPath);
        return;
    }

    printf("Start monitoring changes in the directory: '%s'\n", dirPath);

    char buffer[BUFFER_SIZE];
    DWORD bytesReturned;

    while (TRUE) {
        if (ReadDirectoryChangesW(
            hDir,
            buffer,
            BUFFER_SIZE,
            TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE |
            FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned,
            NULL,
            NULL
        )) {
            FILE_NOTIFY_INFORMATION* pNotify = (FILE_NOTIFY_INFORMATION*)buffer;

            do {
                char fileName[MAX_PATH];
                int nameLength = WideCharToMultiByte(CP_UTF8, 0, pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR), fileName, MAX_PATH, NULL, NULL);
                fileName[nameLength] = '\0';

                switch (pNotify->Action) {
                case FILE_ACTION_ADDED:
                    printf("Created: %s\n", fileName);
                    break;
                case FILE_ACTION_REMOVED:
                    printf("Deleted: %s\n", fileName);
                    break;
                case FILE_ACTION_MODIFIED:
                    printf("Changed: %s\n", fileName);
                    break;
                case FILE_ACTION_RENAMED_OLD_NAME:
                    printf("Renamed (old name): %s\n", fileName);
                    break;
                case FILE_ACTION_RENAMED_NEW_NAME:
                    printf("Renamed (new name): %s\n", fileName);
                    break;
                default:
                    printf("Unknown action: %s\n", fileName);
                    break;
                }

                if (pNotify->NextEntryOffset == 0) break;
                pNotify = (FILE_NOTIFY_INFORMATION*)((char*)pNotify + pNotify->NextEntryOffset);
            } while (TRUE);
        }
        else {
            printf("Error reading directory changes\n");
            break;
        }
    }

    CloseHandle(hDir);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory path>\n", argv[0]);
        return 1;
    }

    char* dirPath = argv[1];

    if (!DirectoryExists(dirPath)) {
        printf("Error: Directory does not exist: %s\n", dirPath);
        return 1;
    }
    ListDirectoryContents(dirPath);
    MonitorDirectory(dirPath);

    return 0;
}