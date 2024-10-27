#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable conditionVariable;
bool turnSequence = true;

void createThread(string threadName) {
    for (int i = 0; i < 90; i++) {
        if (i < 30 || i > 60) {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "����� " << threadName << ". �������� " << i << endl;
        }
        else {
            unique_lock<mutex> lock(mtx);
            conditionVariable.wait(lock, [&] { return (threadName == "A" && turnSequence) || (threadName == "B" && !turnSequence); });

            cout << "����� " << threadName << ". �������� " << i << endl;

            turnSequence = !turnSequence;
            conditionVariable.notify_all();
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    thread A(createThread, "A");
    thread B(createThread, "B");

    A.join();
    B.join();

    cout << "��� ������ ���������" << endl;
    return 0;
}