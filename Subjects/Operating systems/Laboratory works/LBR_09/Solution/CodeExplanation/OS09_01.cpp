#include <iostream>
#include <Windows.h> // ���������� Windows API
#include <string> 
#include <fstream> // ���������� ���������� ��� ������ � �������
#include <locale> // ���������� ���������� ��� �����������
#include <codecvt> // ���������� ���������� ��� ����������� ���������

using namespace std;

LPCWSTR getFileType(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN: {
        return L"��� ����� �� ���������";
    }

    case FILE_TYPE_DISK: {
        return L"���� ��������� �� �����";
    }

    case FILE_TYPE_CHAR: {
        return L"���� �������� ���������� �����������";
    }

    case FILE_TYPE_PIPE: {
        return L"���� ������������ ����� ������������ ��� ��������� �����";
    }

    case FILE_TYPE_REMOTE: {
        return L"���� �������� ���������";
    }

    default: {
        return L"����������� ��� �����";
    }
    }
}


BOOL printFileInfo(LPCWSTR FileName) {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo; // ��������� ��� �������� ���������� � �����

    if (!GetFileAttributesEx(FileName, GetFileExInfoStandard, &fileInfo)) { // ��������� ��������� �����
        wcerr << L"������ ��������� ���������� � �����: " << FileName << endl; // ��������� �� ������
        return FALSE;
    }

    LARGE_INTEGER fileSize; // ���������� ��� �������� ������� �����
    fileSize.LowPart = fileInfo.nFileSizeLow; // ������ ����� ������� �����
    fileSize.HighPart = fileInfo.nFileSizeHigh; // ������� ����� ������� �����

    SYSTEMTIME creationTime, lastWriteTime; // ���������� ��� �������� ������� �������� ���������� ����������
    FileTimeToSystemTime(&fileInfo.ftCreationTime, &creationTime); // ������������ ����� �������� � ��������� �����
    FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &lastWriteTime); // ������������ ����� ���������� ����������

    HANDLE hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // ��������� ���� ��� ������
    if (hFile == INVALID_HANDLE_VALUE) { // ��������� ������� �� ������� ����
        wcerr << L"������ �������� �����: " << FileName << endl;
        return FALSE;
    }

    // ����� ���������� � �����
    wcout << L"��� �����: " << FileName << endl;
    wcout << L"��� �����: " << getFileType(hFile) << endl;
    wcout << L"������ �����: " << fileSize.QuadPart << L" ����" << endl;
    wcout << L"���� � ����� ��������: " << creationTime.wDay << L"." << creationTime.wMonth << L"." << creationTime.wYear << L" "
        << creationTime.wHour << L":" << creationTime.wMinute << L":" << creationTime.wSecond << endl;
    wcout << L"���� � ����� ���������� ����������: " << lastWriteTime.wDay << L"." << lastWriteTime.wMonth << L"." << lastWriteTime.wYear << L" "
        << lastWriteTime.wHour << L":" << lastWriteTime.wMinute << L":" << lastWriteTime.wSecond << endl;

    return TRUE; // �������� ���������� �������
}


BOOL printFileTxt(LPCWSTR FileName) {
    wifstream file(FileName); // ��������� ���� ��� ������� ����-�����
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // ������������� ��������� UTF-8

    if (!file.is_open()) {
        wcerr << L"!!!������!!! ���� �� ��������: " << FileName << endl; // ��������� �� ������
        return FALSE;
    }

    wcout << L"���������� �����:" << endl;
    wstring line; // ���������� ��� �������� ������
    while (getline(file, line)) { // ������ ���� ���������
        wcout << line << endl;
    }

    file.close(); // ��������� ����
    return TRUE;
}

int main() {
    setlocale(LC_ALL, "Rus");
    LPCWSTR fileName = L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_09\\Solution\\file.txt"; 
    printFileInfo(fileName);
	printFileTxt(fileName);

    return 0;
}