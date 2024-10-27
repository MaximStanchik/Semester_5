#include <stdio.h>
#include <locale.h>
#include <string.h>

int Pos_traditionalArrayProcessing(const char* s, const char* s1) {
    if (s == NULL || s1 == NULL) {
        return -2; 
    }
    if (*s1 == '\0') {
        return 0; 
    }

    for (int i = 0; s[i] != '\0'; i++) {
        int j;
        for (j = 0; s1[j] != '\0'; j++) {
            if (s[i + j] != s1[j]) {
                break;
            }
        }
        if (s1[j] == '\0') {
            return i; 
        }
    }
    return -1; 
}

int Pos_addressArithmetic(const char* s, const char* s1) {
    if (s == NULL || s1 == NULL) {
        return -2;
    }
    if (*s1 == '\0') {
        return 0; 
    }

    for (const char* p = s; *p != '\0'; p++) {
        const char* p1 = s1;
        const char* start = p;

        while (*p1 != '\0' && *p == *p1) {
            p++;
            p1++;
        }

        if (*p1 == '\0') {
            return start - s; 
        }

        p = start;
    }
    return -1; 
}

void run_tests() {
    const char* test_cases[][2] = {
        {"Hello, world!", "world!"}, // обычный случай
        {"Hello, world!", "Hello"},   // подстрока в начале
        {"Hello, world!", "!"},       // подстрока в конце
        {"Hello, world!", "notfound"}, // подстрока не найдена
        {"", "Hello"},                 // пустая основная строка
        {"Hello", ""},                 // пустая подстрока
        {"Hello", "Hello"},            // полное совпадение
        {NULL, "world!"},              // ошибка: NULL в основной строке
        {"Hello, world!", NULL}        // ошибка: NULL в подстроке
    };

    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        const char* firstStr = test_cases[i][0];
        const char* substr = test_cases[i][1];

        int posTAPResult = Pos_traditionalArrayProcessing(firstStr, substr);
        int posAAResult = Pos_addressArithmetic(firstStr, substr);

        printf("Test %d: ", i + 1);
        printf("Traditional Array Processing: %d, Address Arithmetic: %d\n", posTAPResult, posAAResult);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    char firstStr[100];
    char substr[100];

    int posTAPResult = Pos_traditionalArrayProcessing(firstStr, substr);
    printf("Using traditional array processing: ");
    if (posTAPResult != -1) {
        printf("substring found at position %d\n", posTAPResult);
    }
    else if (posTAPResult == -2) {
        printf("-2\n");
    }
    else {
        printf("substring not found\n");
    }

    int posAAResult = Pos_addressArithmetic(firstStr, substr);
    printf("Using address arithmetic: ");
    if (posAAResult != -1) {
        printf("substring found at position %d\n", posAAResult);
    }
    else if (posAAResult == -2) {
        printf("Error: one of the parameters is NULL\n");
    }
    else {
        printf("substring not found\n");
    }

    printf("\nRunning tests:\n");
    run_tests();

    return 0;
}
