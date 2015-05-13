#include "DoNotChangeThese.h"
#include <stdio.h>
#define THREAD_COUNT 5
#define NUM_RESOURCES 6

//Type of function pointer.
typedef DWORD(WINAPI *Thread_Function) (LPVOID);
//Use index 1 ~ NUM_RESOURCES to make the index is same as the resource ID.
CRITICAL_SECTION critical_sections[NUM_RESOURCES + 1];
volatile DWORD resource1 = 0;
volatile DWORD resource2 = 0;
volatile DWORD resource3 = 0;
volatile DWORD resource4 = 0;
volatile DWORD resource5 = 0;
volatile DWORD resource6 = 0;

// The following functions should all be in your main program file that you included the header above into
// IMPORTANT: You may ADD to the following functions but you MUST NOT delete anything
// Our tests on your final code will need everything that was there before and will use this to test your code.

void TestCase1()
{
	StartingFunction(1); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 1
	EnterCriticalSection(&critical_sections[1]);
	++resource1;
	UseResource(1);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[1]);
	EndingFunction(1); // Do not remove - for testing purposes
}

void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 2
	EnterCriticalSection(&critical_sections[2]);
	++resource2;
	UseResource(2);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[2]);
	EndingFunction(2); // Do not remove - for testing purposes
}

void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 3
	EnterCriticalSection(&critical_sections[3]);
	++resource3;
	UseResource(3);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[3]);
	EndingFunction(3); // Do not remove - for testing purposes
}

void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 4
	EnterCriticalSection(&critical_sections[4]);
	++resource4;
	UseResource(4);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[4]);
	EndingFunction(4); // Do not remove - for testing purposes
}

void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 5
	EnterCriticalSection(&critical_sections[5]);
	++resource5;
	UseResource(5);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[5]);
	EndingFunction(5); // Do not remove - for testing purposes
}

void TestCase6()
{
	StartingFunction(6); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resources 1 and 2
	EnterCriticalSection(&critical_sections[1]);
	EnterCriticalSection(&critical_sections[2]);
	++resource1;
	++resource2;
	UseTwoResources(1, 2);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[2]);
	LeaveCriticalSection(&critical_sections[1]);
	EndingFunction(6); // Do not remove - for testing purposes
}

void TestCase7()
{
	StartingFunction(7); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resources 2 and 3
	EnterCriticalSection(&critical_sections[2]);
	EnterCriticalSection(&critical_sections[3]);
	++resource2;
	++resource3;
	UseTwoResources(2, 3);	// Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[3]);
	LeaveCriticalSection(&critical_sections[2]);
	EndingFunction(7); // Do not remove - for testing purposes
}

void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 3
	// This order is to avoid deadlock. The entering order is 4-5-6-3.
	EnterCriticalSection(&critical_sections[5]);
	EnterCriticalSection(&critical_sections[3]);
	++resource3;
	int iTemp = StartToUseResource(3); // Do not remove - for testing purposes
	EnterCriticalSection(&critical_sections[6]);
	// TODO - add extra code to increment your value for resources 5 and 6
	++resource5;
	++resource6;
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[6]);
	LeaveCriticalSection(&critical_sections[5]);
	FinishUsingResource(3, iTemp); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[3]);
	EndingFunction(8); // Do not remove - for testing purposes
}

void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 4
	EnterCriticalSection(&critical_sections[4]);
	++resource4;
	int iTemp = StartToUseResource(4); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[4]);
	EndingFunction(9); // Do not remove - for testing purposes
}

void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 1
	EnterCriticalSection(&critical_sections[1]);
	++resource1;
	int iTemp = StartToUseResource(1); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	FinishUsingResource(1, iTemp); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[1]);
	EndingFunction(10); // Do not remove - for testing purposes
}

void TestCase11()
{
	StartingFunction(11); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 3
	// This order is to avoid deadlock. The entering order is 4-5-6-3.
	EnterCriticalSection(&critical_sections[4]);
	EnterCriticalSection(&critical_sections[5]);
	EnterCriticalSection(&critical_sections[3]);
	++resource3;
	int iTemp3 = StartToUseResource(3); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 4
	++resource4;
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	EnterCriticalSection(&critical_sections[6]);
	// TODO - add extra code to increment your value for resources 5 and 6
	++resource5;
	++resource6;
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[6]);
	LeaveCriticalSection(&critical_sections[5]);
	FinishUsingResource(3, iTemp3); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[3]);
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[4]);
	EndingFunction(11); // Do not remove - for testing purposes
}

void TestCase12()
{
	StartingFunction(12); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 5
	EnterCriticalSection(&critical_sections[5]);
	++resource5;
	int iTemp = StartToUseResource(5); // Do not remove - for testing purposes
	TestCase3(); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[5]);
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
	// TODO - add extra code to increment your value for resource 4
	EnterCriticalSection(&critical_sections[4]);
	++resource4;
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 5
	EnterCriticalSection(&critical_sections[5]);
	++resource5;
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 6
	EnterCriticalSection(&critical_sections[6]);
	++resource6;
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[4]);
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[5]);
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[6]);
	EndingFunction(14); // Do not remove - for testing purposes
}

void TestCase15()
{
	StartingFunction(15); // Do not remove - for testing purposes
	EnterCriticalSection(&critical_sections[4]);
	// TODO - add extra code to increment your value for resource 4
	resource4++;
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	EnterCriticalSection(&critical_sections[5]);
	// TODO - add extra code to increment your value for resource 5
	resource5++;
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	EnterCriticalSection(&critical_sections[6]);
	// TODO - add extra code to increment your value for resource 6
	resource6++;
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes
	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[4]);
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[5]);
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes
	LeaveCriticalSection(&critical_sections[6]);
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

	// Implement this to send the information to the server
	// You need to send a value to say which thread/process this is, along with the current values of all resource variables.
	// These window classes are from PartB server.
	HWND hwnd1 = FindWindow("ThreadProgWindow", NULL);
	HWND hwnd2 = FindWindow("ResourceAccessWindow", NULL);

	if (!hwnd1) {
		printf("Thread Progress Window does not exist.\n");
	}
	else{
		PostMessage(hwnd1, WM_USER + 1, iProcessOrThreadID, 0);
	}

	if (!hwnd2){
		printf("Resource Access Window does not exist.\n");
	}
	else{
		PostMessage(hwnd2, WM_USER + 2, 1, resource1);
		PostMessage(hwnd2, WM_USER + 2, 2, resource2);
		PostMessage(hwnd2, WM_USER + 2, 3, resource3);
		PostMessage(hwnd2, WM_USER + 2, 4, resource4);
		PostMessage(hwnd2, WM_USER + 2, 5, resource5);
		PostMessage(hwnd2, WM_USER + 2, 6, resource6);
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


int main(){
	int i;
	// Thread handler array.
	HANDLE thread_handlers[THREAD_COUNT];
	// Function pointer array - to call procedure acorrding to the thread ID.
	Thread_Function thread_procs[5] = { &Procedure1, &Procedure2, &Procedure3, &Procedure4, &Procedure5 };

	//Initialize critical section array.
	for (i = 1; i < NUM_RESOURCES + 1; i++)
	{
		if (!InitializeCriticalSectionAndSpinCount(&critical_sections[i], 1024)){
			printf("Error in Initialize Critical Section %d\n", i);
			return 1;
		}
	}

	//Initialize threads.
	for (i = 0; i < THREAD_COUNT; i++)
	{
		thread_handlers[i] = CreateThread(NULL, 0, thread_procs[i], NULL, 0, NULL);
		if (!thread_handlers[i])
		{
			printf("Error in Creating thread %d\n", i + 1);
			return 1;
		}
	}

	//Wait for all threads.
	WaitForMultipleObjects(THREAD_COUNT, thread_handlers, TRUE, INFINITE);

	//Close all thread handlers.
	for (i = 0; i < THREAD_COUNT; i++)
		CloseHandle(thread_handlers[i]);

	//Release critical sections.
	for (i = 1; i < NUM_RESOURCES + 1; i++)
	{  
		DeleteCriticalSection(&critical_sections[i]);
	}

	printf("Resource1: %d\nResource2: %d\nResource3: %d\nResource4: %d\nResource5: %d\nResource6: %d\n", resource1, resource2, resource3, resource4, resource5, resource6);
	printf("press RETURN to continue...\n");
	while (getchar() != '\n')
		;
	return 0;
}