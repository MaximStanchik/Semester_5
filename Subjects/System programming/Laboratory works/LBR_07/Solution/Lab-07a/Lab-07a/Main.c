#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    char Name[64];
    char Surname[128];
    unsigned char Course;
    unsigned char Group;
    char ID[8];
};

// Глобальные переменные
HANDLE hFileMapping = NULL;
struct Student* pStudents = NULL;
int listSize = 0;

int OpenMapping(LPSTR filePath, LPINT size) {
    HANDLE hFile = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to open or create file: %s\n", filePath);
        return GetLastError();
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        CloseHandle(hFile);
        fprintf(stderr, "Failed to get file size \n");
        return GetLastError();
    }

    if (fileSize == 0) {
        *size = MAX_STUDENTS;
        struct Student emptyStudent = { 0 };
        for (int i = 0; i < *size; i++) {
            WriteFile(hFile, &emptyStudent, sizeof(struct Student), NULL, NULL);
        }
        WriteFile(hFile, size, sizeof(int), NULL, NULL);
        listSize = *size; // Обновляем listSize
    }
    else {
        ReadFile(hFile, size, sizeof(int), NULL, NULL);
        listSize = *size; // Обновляем listSize
    }

    hFileMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, sizeof(struct Student) * listSize, "StudentMapping");
    if (hFileMapping == NULL) {
        CloseHandle(hFile);
        fprintf(stderr, "Failed to create mapping \n");
        return GetLastError();
    }

    pStudents = (struct Student*)MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(struct Student) * listSize);
    if (pStudents == NULL) {
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        fprintf(stderr, "Failed to map mapping to memory \n");
        return GetLastError();
    }

    CloseHandle(hFile); // Закрываем hFile, так как он больше не нужен
    return 0;
}

int AddRow(struct Student row, INT pos) {
    if (hFileMapping == NULL || pStudents == NULL) {
        fprintf(stderr, "Error: mapping is not open \n");
        return -1;
    }

    if (pos < 0) {
        pos += listSize;
    }

    if (pos < 0 || pos >= listSize) {
        fprintf(stderr, "Error: position out of range. Entered: %d\n", pos);
        return -2;
    }

    if (pStudents[pos].ID[0] != '\0') {
        fprintf(stderr, "Error: position %d is occupied, please select another \n", pos);
        return -3;
    }

    pStudents[pos] = row;
    return 0;
}

int RemRow(INT lineNumber) {
    if (hFileMapping == NULL || pStudents == NULL) return -1;
    if (lineNumber < 0 || lineNumber >= listSize) {
        fprintf(stderr, "Error: Line number is out of range. Entered: %d\n", lineNumber);
        return -2;
    }

    if (pStudents[lineNumber].ID[0] == '\0') {
        fprintf(stderr, "Error: line %d is empty, do not delete anything \n", lineNumber);
        return -2;
    }

    memset(&pStudents[lineNumber], 0, sizeof(struct Student));
    return 0;
}

int PrintRow(INT pos) {
    if (hFileMapping == NULL || pStudents == NULL) return -1;
    if (pos < 0) pos += listSize;
    if (pos < 0 || pos >= listSize || pStudents[pos].ID[0] == '\0') return -2;

    printf("Name: %s, Surname: %s, Course: %u, Group: %u, ID: %s\n",
        pStudents[pos].Name, pStudents[pos].Surname,
        pStudents[pos].Course, pStudents[pos].Group, pStudents[pos].ID);
    return 0;
}

int PrintRows() {
    if (hFileMapping == NULL || pStudents == NULL) return -1;

    for (int i = 0; i < listSize; i++) {
        if (pStudents[i].ID[0] != '\0') {
            PrintRow(i);
        }
    }
    return 0;
}

int CloseMapping() {
    if (hFileMapping == NULL) return -1;

    UnmapViewOfFile(pStudents);
    CloseHandle(hFileMapping);
    hFileMapping = NULL;
    return 0;
}

void displayMenu() {
    printf("1. Open file\n");
    printf("2. Add student\n");
    printf("3. Delete student\n");
    printf("4. Show student\n");
    printf("5. Show all students\n");
    printf("6. Close program\n");
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Choose action: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char filePath[256];
            printf("Enter filename: ");
            scanf("%s", filePath);

            if (OpenMapping(filePath, &listSize) != 0) {
                fprintf(stderr, "Error when opening mapping \n");
            }
            else {
                printf("File opened successfully \n");
            }
        }
        else if (choice == 2) {
            struct Student newStudent;
            printf("Enter name: ");
            scanf("%s", newStudent.Name, sizeof(newStudent.Name));
            printf("Enter surname: ");
            scanf("%s", newStudent.Surname, sizeof(newStudent.Surname));
            printf("Enter course: ");
            scanf("%hhu", &newStudent.Course);
            printf("Enter group: ");
            scanf("%hhu", &newStudent.Group);
            printf("Enter ID: ");
            scanf("%s", newStudent.ID, sizeof(newStudent.ID));

            int position;
            printf("Enter the position to add (negative value to add from the end): ");
            scanf("%d", &position);

            if (AddRow(newStudent, position) != 0) {
                fprintf(stderr, "Error adding student \n");
            }
        }
        else if (choice == 3) {
            int pos;
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            if (RemRow(pos) != 0) {
                fprintf(stderr, "Error when deleting a student \n");
            }
        }
        else if (choice == 4) {
            int pos;
            printf("Enter position to display: ");
            scanf("%d", &pos);
            if (PrintRow(pos) != 0) {
                fprintf(stderr, "Error showing student \n");
            }
        }
        else if (choice == 5) {
            if (PrintRows() != 0) {
                fprintf(stderr, "Error when showing all students \n");
            }
        }
        else if (choice == 6) {
            CloseMapping();
            break;
        }
        else {
            printf("Wrong choice. Try again \n");
        }
    }

    return 0;
}