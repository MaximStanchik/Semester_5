#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

const char* GetBinaryFileType(const char* FileName);

void PrintInfo(const char* FileName) {
    struct stat fileInfo;
    if (stat(FileName, &fileInfo) != 0) {
        perror("Error: Could not get file information");
        return;
    }

    const char* baseName = strrchr(FileName, '\\');
    if (baseName == NULL) {
        baseName = strrchr(FileName, '/');
    }
    if (baseName != NULL) {
        baseName++;
    }
    else {
        baseName = FileName;
    }

    long long size = fileInfo.st_size;
    printf("File name: %s\n", baseName);

    printf("File size: %lld byte (%.2f KiB, %.2f MiB)\n",
        size,
        size / 1024.0,
        size / (1024.0 * 1024.0));

    char timeBuffer[26];
    ctime_s(timeBuffer, sizeof(timeBuffer), &fileInfo.st_ctime);
    printf("Creation time: %s", timeBuffer);
    ctime_s(timeBuffer, sizeof(timeBuffer), &fileInfo.st_atime);
    printf("Last access time: %s", timeBuffer);
    ctime_s(timeBuffer, sizeof(timeBuffer), &fileInfo.st_mtime);
    printf("Last modified time: %s", timeBuffer);

    if (IsTextFile(FileName)) {
        printf("File type: Text file\n");
    }
    else {
        printf("File type: Binary file\n");
        const char* fileType = GetBinaryFileType(FileName);
        printf("Binary file type: %s\n", fileType);
    }
}

int IsTextFile(const char* FileName) {
    FILE* file = fopen(FileName, "rb");
    if (!file) {
        perror("Error: Could not open file");
        return 0;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c < 0 || c == '\0') {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

const char* GetBinaryFileType(const char* FileName) {
    const char* dot = strrchr(FileName, '.');
    if (!dot || dot == FileName) {
        return "Unknown binary type";
    }

    if (strcmp(dot + 1, "docx") == 0) return "Microsoft Word Document";
    if (strcmp(dot + 1, "jpg") == 0 || strcmp(dot + 1, "jpeg") == 0) return "JPEG Image";
    if (strcmp(dot + 1, "png") == 0) return "PNG Image";
    if (strcmp(dot + 1, "pdf") == 0) return "PDF Document";

    return "Unknown binary type"; 
}

void PrintText(const char* FileName) {
    if (!IsTextFile(FileName)) {
        printf("The file is not text\n");
        return;
    }

    FILE* file = fopen(FileName, "r");
    if (!file) {
        perror("Error: Could not open file");
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char* fileName = argv[1];
    PrintInfo(fileName);
    printf("\nFile contents:\n");
    PrintText(fileName);

    return 0;
}


//D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\SystemProgramming\\LaboratoryWorks\\LBR_06\\Solution\\file.txt
//D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\SystemProgramming\\LaboratoryWorks\\LBR_06\\Solution\\Report.docx