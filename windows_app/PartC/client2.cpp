#undef UNICODE

// Turn off warnings for using sprintf - which is unsafe, as it states, but portable
#define _CRT_SECURE_NO_WARNINGS 1


// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN

// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include "DoNotChangeThese.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 8000
#define DEFAULT_ADDR "127.0.0.1"

// And choose a size for the buffer for data - make it big enough for any input
#define DEFAULT_BUFLEN 512

// Number of client processes to start
#define NUM_CLIENTS 5
#define NUM_RESOURCES 6

// Message structrue of client
struct DataClientToServer
{
	int clientID;
	DWORD resource7;
	DWORD resource8;
	DWORD resource9;
	DWORD resource10;
	DWORD resource11;
	DWORD resource12;
};

union WrapperDataClientToServer
{
	DataClientToServer a;
	char b[sizeof(DataClientToServer)];
};

// Resource structrue for map file
struct ResourceStructure
{
	volatile DWORD resource1 = 0;
	volatile DWORD resource2 = 0;
	volatile DWORD resource3 = 0;
	volatile DWORD resource4 = 0;
	volatile DWORD resource5 = 0;
	volatile DWORD resource6 = 0;
};

volatile ResourceStructure * pMyData;
//Use index 1 ~ NUM_RESOURCES + 1 to make the index is same as the resource ID.
HANDLE mutex_objects[NUM_RESOURCES + 1];
//type of function pointer
typedef DWORD(WINAPI *Thread_Function) (LPVOID);
SOCKET ConnectSocket;

// The following functions should all be in your main program file that you included the header above into
// IMPORTANT: You may ADD to the following functions but you MUST NOT delete anything
// Our tests on your final code will need everything that was there before and will use this to test your code.

void TestCase1()
{
	StartingFunction(1); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[1], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 1
	++pMyData->resource1;
	UseResource(1);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[1]);
	EndingFunction(1); // Do not remove - for testing purposes
}

void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[2], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 2
	++pMyData->resource2;
	UseResource(2);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[2]);
	EndingFunction(2); // Do not remove - for testing purposes
}

void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[3], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 3
	++pMyData->resource3;
	UseResource(3);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[3]);
	EndingFunction(3); // Do not remove - for testing purposes
}

void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[4], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 4
	++pMyData->resource4;
	UseResource(4);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[4]);
	EndingFunction(4); // Do not remove - for testing purposes
}

void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[5], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 5
	++pMyData->resource5;
	UseResource(5);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[5]);
	EndingFunction(5); // Do not remove - for testing purposes
}

void TestCase6()
{
	StartingFunction(6); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[1], INFINITE) != WAIT_OBJECT_0) return;
	if (WaitForSingleObject(mutex_objects[2], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resources 1 and 2
	++pMyData->resource1;
	++pMyData->resource2;
	UseTwoResources(1, 2);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[2]);
	ReleaseMutex(mutex_objects[1]);
	EndingFunction(6); // Do not remove - for testing purposes
}

void TestCase7()
{
	StartingFunction(7); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[2], INFINITE) != WAIT_OBJECT_0) return;
	if (WaitForSingleObject(mutex_objects[3], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resources 2 and 3
	++pMyData->resource2;
	++pMyData->resource3;
	UseTwoResources(2, 3);	// Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[3]);
	ReleaseMutex(mutex_objects[2]);
	EndingFunction(7); // Do not remove - for testing purposes
}

void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[5], INFINITE) != WAIT_OBJECT_0) return;
	if (WaitForSingleObject(mutex_objects[3], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 3
	++pMyData->resource3;
	int iTemp = StartToUseResource(3); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[6], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resources 5 and 6
	++pMyData->resource5;
	++pMyData->resource6;
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[5]);
	ReleaseMutex(mutex_objects[6]);
	FinishUsingResource(3, iTemp); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[3]);
	EndingFunction(8); // Do not remove - for testing purposes
}

void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[4], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 4
	++pMyData->resource4;
	int iTemp = StartToUseResource(4); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[4]);
	EndingFunction(9); // Do not remove - for testing purposes
}

void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[1], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 1
	++pMyData->resource1;
	int iTemp = StartToUseResource(1); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	FinishUsingResource(1, iTemp); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[1]);
	EndingFunction(10); // Do not remove - for testing purposes
}

void TestCase11()
{
	StartingFunction(11); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[4], INFINITE) != WAIT_OBJECT_0) return;
	if (WaitForSingleObject(mutex_objects[5], INFINITE) != WAIT_OBJECT_0) return;
	if (WaitForSingleObject(mutex_objects[3], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 3
	++pMyData->resource3;
	int iTemp3 = StartToUseResource(3); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 4
	++pMyData->resource4;
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[6], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resources 5 and 6
	++pMyData->resource5;
	++pMyData->resource6;
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[5]);
	ReleaseMutex(mutex_objects[6]);
	FinishUsingResource(3, iTemp3); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[3]);
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[4]);
	EndingFunction(11); // Do not remove - for testing purposes
}

void TestCase12()
{
	StartingFunction(12); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[5], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 5
	++pMyData->resource5;
	int iTemp = StartToUseResource(5); // Do not remove - for testing purposes
	TestCase3(); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[5]);
	EndingFunction(12); // Do not remove - for testing purposes
}

void TestCase13()
{
	StartingFunction(13); // Do not remove - for testing purposes

	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase8(); // Do not remove - for testing purposes

	EndingFunction(13); // Do not remove - for testing purposes
}

void TestCase14()
{
	StartingFunction(14); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[4], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 4
	++pMyData->resource4;
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[5], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 5
	++pMyData->resource5;
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[6], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 6
	++pMyData->resource6;
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[4]);
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[5]);
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[6]);

	EndingFunction(14); // Do not remove - for testing purposes
}

void TestCase15()
{
	StartingFunction(15); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[4], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 4
	++pMyData->resource4;
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[5], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 5
	++pMyData->resource5;
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	if (WaitForSingleObject(mutex_objects[6], INFINITE) != WAIT_OBJECT_0) return;
	// TODO - add extra code to increment your value for resource 6
	++pMyData->resource6;
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes

	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[4]);
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[5]);
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes
	ReleaseMutex(mutex_objects[6]);

	EndingFunction(15); // Do not remove - for testing purposes
}

void InitialCode(int iDelay)
{
	StartingFunction(-1); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay);
	EndingFunction(-1); // Do not remove - for testing purposes
}

void RemainderCode(int iDelay)
{
	StartingFunction(-2); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay); // Do not remove - for testing purposes
	EndingFunction(-2); // Do not remove - for testing purposes
}

void SendDataToServer(int iProcessOrThreadID)
{
	StartingFunction(-3); // Do not remove - for testing purposes
	int iResult;
	WrapperDataClientToServer message;

	message.a.clientID = iProcessOrThreadID + 5;
	message.a.resource7 = pMyData->resource1;
	message.a.resource8 = pMyData->resource2;
	message.a.resource9 = pMyData->resource3;
	message.a.resource10 = pMyData->resource4;
	message.a.resource11 = pMyData->resource5;
	message.a.resource12 = pMyData->resource6;

	iResult = send(ConnectSocket, message.b, (int)sizeof(message), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("ConnectSocket send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		return;
	}

	EndingFunction(-3); // Do not remove - for testing purposes
}


// Thread 1 should run this
DWORD WINAPI Procedure1(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase1(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase11(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(1); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 2 should run this
DWORD WINAPI Procedure2(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase2(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase12(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(2); // Do not remove - for testing purposes
	}
	return 1;
}

// Thread 3 should run this
DWORD WINAPI Procedure3(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase3(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase8(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase13(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(3); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 4 should run this
DWORD WINAPI Procedure4(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase4(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase9(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase14(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(4); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 5 should run this
DWORD WINAPI Procedure5(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase5(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase10(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase15(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(5); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

void StartClients(PROCESS_INFORMATION* process_infos)
{
	for (int i = 0; i < NUM_CLIENTS; i++)
	{
		// Work out the filename of the exe for the running process
		char szMyFileName[1024];
		GetModuleFileName(NULL, szMyFileName, 1024);
		char szCommandLine[1024 + 4];
		// Wait 5 seconds to give me time to kill stuff if it goes wrong? Uncomment the next line if you are worried.
		//Sleep(5000);

		// Set up command line arguments
		sprintf(szCommandLine, "\"%s\" %d", szMyFileName, i + 1/*Client number*/);
		STARTUPINFO info = { sizeof(info) }; // Input
		PROCESS_INFORMATION processInfo; // Output
		printf("Starting Client %d ...\n", i);
		if (!CreateProcess(
			szMyFileName, // Program
			szCommandLine,// Command line
			NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE,
			NULL, NULL,
			&info,
			&process_infos[i]))
		{
			printf("Error in Starting Client %d ...\n", i);
			return;
		}
	}
}

int main(int argc, char* argv[]){
	int i;
	HANDLE hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0, sizeof(ResourceStructure), // max size high,low DWORDs
		"Local\\MyFileMappingObject"); // name of mapping object

	if (hMapFile == NULL)
	{
		printf("Could not create file mapping object (%d).\n",
			GetLastError());
		return 1;
	}

	pMyData =
		(ResourceStructure *)MapViewOfFile(
		hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		sizeof(ResourceStructure));

	if (pMyData == NULL)
	{
		printf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}

	for (i = 1; i < NUM_RESOURCES + 1; i++)
	{
		char tag[25];
		_itoa(i, tag, 10);
		strcat(tag, "mutex"); //Create different name for mutex object.
		mutex_objects[i] = CreateMutex(NULL, FALSE, tag);
		if (!mutex_objects[i])
		{
			printf("Could not create mutex object (%d).\n", GetLastError());
			return 1;
		}
	}

	if (argc > 1)
	{
		WSADATA wsaData;
		// Initialize Winsock

		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		printf("Process %d with Procedure %d is running...\n", atoi(argv[1]), atoi(argv[1]));
		Thread_Function thread_functions[5] = { &Procedure1, &Procedure2, &Procedure3, &Procedure4, &Procedure5 };
		ConnectSocket = INVALID_SOCKET;
		int recvbuflen = DEFAULT_BUFLEN;

		struct sockaddr_in serveraddress;
		serveraddress.sin_family = AF_INET;
		serveraddress.sin_addr.s_addr = inet_addr(DEFAULT_ADDR); // Local machine
		serveraddress.sin_port = htons(DEFAULT_PORT);

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("ConnectSocket socket failed with error: %ld\n", WSAGetLastError());
		}
		else
		{
			//Connect to Server
			iResult = connect(ConnectSocket, (sockaddr*)&serveraddress, sizeof(serveraddress));
			if (iResult == SOCKET_ERROR)
			{
				printf("ConnectSocket connect failed with error: %ld\n", WSAGetLastError());
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
			}
			thread_functions[atoi(argv[1]) - 1](NULL);
			iResult = shutdown(ConnectSocket, SD_SEND);
			if (iResult == SOCKET_ERROR)
			{
				printf("ConnectSocket shutdown failed with error: %d\n", WSAGetLastError());
			}
			closesocket(ConnectSocket);
			printf("Process %d done\n", atoi(argv[1]));
			printf("Resource1: %d\nResource2: %d\nResource3: %d\nResource4: %d\nResource5: %d\nResource6: %d\n", pMyData->resource1, pMyData->resource2, pMyData->resource3,
				pMyData->resource4, pMyData->resource5, pMyData->resource6);
		}
		WSACleanup();
	}
	else
	{
		PROCESS_INFORMATION process_infos[NUM_CLIENTS];
		StartClients(process_infos);

		for (i = 0; i < NUM_CLIENTS; i++)
		{
			WaitForSingleObject(process_infos[i].hProcess, INFINITE);
			WaitForSingleObject(process_infos[i].hThread, INFINITE);
		}

		for (i = 0; i < NUM_CLIENTS; i++)
		{
			CloseHandle(process_infos[i].hProcess);
			CloseHandle(process_infos[i].hThread);
		}

		printf("Resource1: %d\nResource2: %d\nResource3: %d\nResource4: %d\nResource5: %d\nResource6: %d\n", pMyData->resource1, pMyData->resource2, pMyData->resource3,
			pMyData->resource4, pMyData->resource5, pMyData->resource6);
	}

	for (i = 1; i < NUM_RESOURCES + 1; i++)
	{
		CloseHandle(mutex_objects[i]);
	}

	UnmapViewOfFile((LPCVOID)pMyData);
	CloseHandle(hMapFile);

	printf("Press ENTER to exit\n");
	while (getchar() != '\n')
		;
	return 0;
}
