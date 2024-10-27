#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");

	wchar_t Lab02x_path[] = L"D:/User/Desktop/StudyAtBSTU/Course_3/Semester5/Subjects/SystemProgramming/LaboratoryWorksL/BR_02/Solution/NewSolution/Lab-02x/Lab-02x/x64/Debug/Lab-02x.exe";

	HANDLE hProcesses[3] = {NULL, NULL, NULL};
	wchar_t commandLine[] = L"Lab-02x.exe";
	wchar_t commandLineWithArgs[200];

	PROCESS_INFORMATION firstProcessInfo, secondProcessInfo, thirdProcessInfo;
	STARTUPINFO firstStartupInfo, secondStartupInfo, thirdStartupInfo;

	ZeroMemory(&firstStartupInfo, sizeof(firstStartupInfo));
	firstStartupInfo.cb = sizeof(firstStartupInfo);
	ZeroMemory(&firstProcessInfo, sizeof(firstProcessInfo));

	ZeroMemory(&secondStartupInfo, sizeof(secondStartupInfo));
	secondStartupInfo.cb = sizeof(secondStartupInfo);
	ZeroMemory(&secondProcessInfo, sizeof(secondProcessInfo));

	ZeroMemory(&thirdStartupInfo, sizeof(thirdStartupInfo));
	thirdStartupInfo.cb = sizeof(thirdStartupInfo);
	ZeroMemory(&thirdProcessInfo, sizeof(thirdProcessInfo));

	cout << "Попытка создания первого процесса..." << endl;
	if (!CreateProcess(
		Lab02x_path,   
		NULL,          
		NULL,          
		NULL,          
		FALSE,         
		0,            
		NULL,          
		NULL,          
		&firstStartupInfo, 
		&firstProcessInfo  
	)) {
		cout << "Ошибка при создании первого процесса: " << GetLastError() << endl;
	}
	else {
		cout << "Первый процесс создан и запущен с ID: " << GetCurrentProcessId() << endl;
		hProcesses[0] = firstProcessInfo.hProcess;
		CloseHandle(firstProcessInfo.hThread);
	}

	cout << "Попытка создания второго процесса..." << endl;
	if (!CreateProcess(
		NULL,   
		commandLine,          
		NULL,          
		NULL,        
		FALSE,         
		0,            
		NULL,          
		NULL,          
		&secondStartupInfo, 
		&secondProcessInfo  
	)) {
		cout << "Ошибка при создании второго процесса: " << GetLastError() << endl;
	}
	else {
		cout << "Второй процесс создан и запущен с ID: " << GetCurrentProcessId() << endl;
		hProcesses[1] = secondProcessInfo.hProcess;
		CloseHandle(secondProcessInfo.hThread);
	}

	cout << "Попытка создания третьего процесса..." << endl;
	if (!CreateProcess(
		Lab02x_path,           
		commandLineWithArgs,
		NULL,          
		NULL,          
		FALSE,         
		0,             
		NULL,         
		NULL,         
		&thirdStartupInfo,     
		&thirdProcessInfo      
	)) {
		cout << "Ошибка при создании третьего процесса: " << GetLastError() << endl;
	}
	else {
		cout << "Третий процесс создан и запущен с ID: " << GetCurrentProcessId() << endl;
		hProcesses[2] = thirdProcessInfo.hProcess;
		CloseHandle(thirdProcessInfo.hThread);
	}

	for (int i = 0; i < 3; i++) {
		if (hProcesses[i] != NULL) {
			DWORD waitResult = WaitForSingleObject(hProcesses[i], INFINITE);
			if (waitResult == WAIT_FAILED) {
				cout << "Ошибка ожидания завершения " << i << "-го процесса: " << GetLastError() << endl;
			}
			CloseHandle(hProcesses[i]);
		}
	}

	ExitProcess(0);
	return 0;
}