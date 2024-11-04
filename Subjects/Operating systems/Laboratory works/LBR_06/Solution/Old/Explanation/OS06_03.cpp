#include <iostream> 
#include <Windows.h> 
using namespace std;

PROCESS_INFORMATION createProcess(LPCWSTR filePath) {
	STARTUPINFO startupInfo; // структура для хранения информации о запуске процесса
	PROCESS_INFORMATION processInfo; // структура для хранения информации о созданном процессе

	ZeroMemory(&startupInfo, sizeof(STARTUPINFO)); // обнуляем память стркутуры startupInfo
	startupInfo.cb = sizeof(STARTUPINFO); // указываем размер структуры для корректной работы API

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
	HANDLE mutex; // дескриптор мьютекса
	HANDLE processes[procSize];

	mutex = CreateMutex(NULL, FALSE, L"OS06_03");

	processes[0] = createProcess(L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_06\\Solution\\Ex_3\\OS06_03\\OS06_03\\x64\\Debug\\OS06_03A.exe").hProcess;
	processes[1] = createProcess(L"D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\OperatingSystems\\LaboratoryWorks\\LBR_06\\Solution\\Ex_3\\OS06_03\\OS06_03\\x64\\Debug\\OS06_03B.exe").hProcess;

	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			WaitForSingleObject(mutex, INFINITE); // блокируем мьютекс, чтобы обеспечить эксклюзивный доступ
			//mutex -- дескриптор объекта синхронизации, который в данном случае является мьютексом. Функция будет ожидать, пока мьютекс не станет доступен для текущего потока
			// INFINITE -- функция будет ждать бесконечно, пока не получит доступ к указанному объекту (в данном случае к мьютексу). Если мьютекс занят другим потоком, текущий поток будет заблокирован до тех пор, пока мьютекс не будет освобожден.
		}
		else if (i == 60) {
			ReleaseMutex(mutex); // освобождение мьютекса (теперь другие потоки могут его использовать)
		}

		Sleep(100);
	}

	WaitForMultipleObjects(procSize, processes, TRUE, INFINITE); // ожидание завершения всех процессов в массиве
	//procSize -- количество объектов, которые вы хотите отслеживать. В данном случае оно указывает, сколько процессов вы ожидаете завершить
	//processes -- массив дескрипторов объектов (в данном случае процессов), которые вы хотите отслеживать. Функция будет ожидать, пока все процессы, указанные в этом массиве, не завершатся.
	//TRUE -- параметр указывает, что функция должна ждать, пока все указанные объекты не станут сигнальными. Если бы вы передали FALSE, функция ждала бы, пока хотя бы один из объектов не станет сигнальным
	//INFINITE -- значение указывает, что функция будет ждать бесконечно, пока не произойдет событие, которое сделает дескрипторы сигнальными (в данном случае, пока все процессы не завершатся)
	for (int i = 0; i < procSize; i++) {
		CloseHandle(processes[i]);
	}

	CloseHandle(mutex);

	return 0;
}