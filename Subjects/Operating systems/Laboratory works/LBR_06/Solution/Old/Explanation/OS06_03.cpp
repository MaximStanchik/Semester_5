#include <iostream> 
#include <Windows.h> 
using namespace std;

PROCESS_INFORMATION createProcess(LPCWSTR filePath) {
	STARTUPINFO startupInfo; // ��������� ��� �������� ���������� � ������� ��������
	PROCESS_INFORMATION processInfo; // ��������� ��� �������� ���������� � ��������� ��������

	ZeroMemory(&startupInfo, sizeof(STARTUPINFO)); // �������� ������ ��������� startupInfo
	startupInfo.cb = sizeof(STARTUPINFO); // ��������� ������ ��������� ��� ���������� ������ API

	if (CreateProcessW(filePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo)) {
		cout << "Process created\n" << endl;
	}
	else {
		cout << "[ERROR] CreateProcessW\n";
	}

	return processInfo;
}

int main() {
	setlocale(LC_ALL, "Rus");

	const int procSize = 2;
	HANDLE mutex; // ���������� ��������
	HANDLE processes[procSize];

	mutex = CreateMutex(NULL, FALSE, L"OS06_03");

	processes[0] = createProcess(L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_06\\Solution\\Ex_3\\OS06_03\\OS06_03\\x64\\Debug\\OS06_03A.exe").hProcess;
	processes[1] = createProcess(L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_06\\Solution\\Ex_3\\OS06_03\\OS06_03\\x64\\Debug\\OS06_03B.exe").hProcess;

	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			WaitForSingleObject(mutex, INFINITE); // ��������� �������, ����� ���������� ������������ ������
			//mutex -- ���������� ������� �������������, ������� � ������ ������ �������� ���������. ������� ����� �������, ���� ������� �� ������ �������� ��� �������� ������
			// INFINITE -- ������� ����� ����� ����������, ���� �� ������� ������ � ���������� ������� (� ������ ������ � ��������). ���� ������� ����� ������ �������, ������� ����� ����� ������������ �� ��� ���, ���� ������� �� ����� ����������.
		}
		else if (i == 60) {
			ReleaseMutex(mutex); // ������������ �������� (������ ������ ������ ����� ��� ������������)
		}

		Sleep(100);
	}

	WaitForMultipleObjects(procSize, processes, TRUE, INFINITE); // �������� ���������� ���� ��������� � �������
	//procSize -- ���������� ��������, ������� �� ������ �����������. � ������ ������ ��� ���������, ������� ��������� �� �������� ���������
	//processes -- ������ ������������ �������� (� ������ ������ ���������), ������� �� ������ �����������. ������� ����� �������, ���� ��� ��������, ��������� � ���� �������, �� ����������.
	//TRUE -- �������� ���������, ��� ������� ������ �����, ���� ��� ��������� ������� �� ������ �����������. ���� �� �� �������� FALSE, ������� ����� ��, ���� ���� �� ���� �� �������� �� ������ ����������
	//INFINITE -- �������� ���������, ��� ������� ����� ����� ����������, ���� �� ���������� �������, ������� ������� ����������� ����������� (� ������ ������, ���� ��� �������� �� ����������)
	for (int i = 0; i < procSize; i++) {
		CloseHandle(processes[i]);
	}

	CloseHandle(mutex);

	return 0;
}