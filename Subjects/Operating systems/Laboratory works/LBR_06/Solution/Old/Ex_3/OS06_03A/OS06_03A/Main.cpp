#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	int pid = GetCurrentProcessId();
	HANDLE mutex = OpenMutex(SYNCHRONIZE, FALSE, L"Global\\OS06_03");

	if (mutex == NULL) {
		cout << "[ERROR] OpenMutex failed with error: " << GetLastError() << endl;
		return 1; 
	}
	else if (mutex == INVALID_HANDLE_VALUE) {
		cout << "[ERROR] OpenMutex failed with error: " << GetLastError() << endl;
		return 1;
	}
	else {
		for (int i = 1; i <= 90; ++i)
		{
			if (i == 30) {
				WaitForSingleObject(mutex, INFINITE);
				printf("Mutex taken!\n");
			}


			else if (i == 60) {
				ReleaseMutex(mutex);
			}


			printf("[OS06_03A]\t%d.  PID = %d\n", i, pid);
			Sleep(100);
		}

		if (mutex)
		{
			CloseHandle(mutex);
		}
	}

	
}