#include <iostream>
#include <Windows.h>

using namespace std;

bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) { // Проверка делителей до квадратного корня из number
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    if (argc < 2) {
        cout << "Не указано время выполнения." << endl;
        return 1;
    }

    int duration = atoi(argv[1]); // Преобразование первого аргумента в целое число

    if (duration <= 0) {
        cout << "Время выполнения должно быть положительным." << endl;
        return 1;
    }

    DWORD startTime = timeGetTime(); // Запись начального времени в миллисекундах

    int number = 2;
    int count = 1;

    while (true) {
        if (timeGetTime() - startTime >= duration) { // если вышло время, выход из цикла
            break; 
        }

        if (isPrime(number)) { // вывод простых чисел
            cout << count << ": " << number << "." << endl;
            count++;
            Sleep(500); 
        }
        number++; // переход к следующему числу
    }
    system("pause");
    return 0;
}