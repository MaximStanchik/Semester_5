#include <iostream> // ����������� ���������� ��� ����� � ������
#include <windows.h> // ����������� ���������� Windows API ��� ������ � �����

using namespace std; // ������������� ������������ ���� std

void sh(HANDLE heap); // ���������� ������� ��� ����������� ���������� � ����

int main() { // �������� ������� ���������
    setlocale(LC_ALL, "Rus"); // ��������� ������� ������ ��� ����������� ������

    // �������� ����� ���� � �������� 4 �� � ���������� ���������� ��� �������
    HANDLE heap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 4 * 1024 * 1024, 0);
    if (heap == nullptr) { // �������� ���������� �������� ����
        cerr << "������ �������� ����." << endl; // ����� ��������� �� ������
        return 1; // ���������� ��������� � ����� ������
    }

    cout << "�� ���������� �������: " << endl; // ��������� ����� ����������� �������
    sh(heap); // ����� ������� ��� ����������� ���������� � ����

    const int size = 300000; // ����������� ������� ������� (300000 ���������)
    // ��������� ������ ��� ������� � ����
    int* newArray = (int*)HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, size * sizeof(int));
    if (newArray == nullptr) { // �������� ���������� ��������� ������
        cerr << "������ ���������� ������� � ����." << endl; // ����� ��������� �� ������
        HeapDestroy(heap); // ������������ �������� ����
        return 1; // ���������� ��������� � ����� ������
    }

    cout << "����� ���������� �������: " << endl; // ��������� ����� ���������� �������
    sh(heap); // ����� ������� ��� ����������� ���������� � ����

    HeapFree(heap, 0, newArray); // ������������ ���������� ������ � ����

    // ������������ �������� ����
    if (!HeapDestroy(heap)) {
        cerr << "������ ������������ ����." << endl; // ��������� �� ������
        return 1; // ���������� ��������� � ����� ������
    }

    return 0; // ���������� ��������� � ����� ������
}

// ������� ��� ����������� ���������� � ����
void sh(HANDLE heap) {
    PROCESS_HEAP_ENTRY entry; // ��������� ��� �������� ���������� � ������ � ����
    entry.lpData = nullptr; // ������������� ��������� �� ������

    SIZE_T allocatedMemorySize = 0; // ���������� ��� �������� ������� ���������� ������
    SIZE_T unallocatedMemorySize = 0; // ���������� ��� �������� ������� ������������ ������

    // ���� �� ���� ������� � ����
    while (HeapWalk(heap, &entry)) {
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) { // ��������, ������ �� ������
            allocatedMemorySize += entry.cbData; // ���������� ������� ���������� ������
        }
        else {
            unallocatedMemorySize += entry.cbData; // ���������� ������� ������������ ������
        }
    }

    SIZE_T totalHeapSize = allocatedMemorySize + unallocatedMemorySize; // ����� ������ ����

    // ����� ���������� � ����
    cout << "����� ������ heap: " << totalHeapSize << " ����" << endl;
    cout << "������ �������������� ������� ������ heap: " << allocatedMemorySize << " ����" << endl;
    cout << "������ ���������������� ������� ������ heap: " << unallocatedMemorySize << " ����" << endl;
}