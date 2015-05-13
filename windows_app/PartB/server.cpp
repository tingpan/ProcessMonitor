#undef UNICODE

// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN

// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

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

#define NUM_RESOURCES 12
#define NUM_CLIENTS  10

int iResValues[NUM_RESOURCES] = { 0 };
int iClientValues[NUM_CLIENTS] = { 0 };

struct DataForThread
{
	SOCKET ClientSocket;
	int iConnectionNumber;
};

// Message structrue from client
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

// Handler for Thread process window
LRESULT CALLBACK WndProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		{
			int aiValuesToShow[NUM_CLIENTS];
			// Todo - copy the values of your resources into the array above
			// e.g.	for ( int i = 0; i < NUM_CLIENTS; i++ )	aiValuesToShow[i] = iClientValues[i];
			for (int i = 0; i < NUM_CLIENTS; i++)
				aiValuesToShow[i] = iClientValues[i];
			// Now work out how high to make each bar
			int iMax = -10000000; int iMin = 10000000;
			for (int i = 0; i < 10; i++)
			{
				if (aiValuesToShow[i] < iMin) iMin = aiValuesToShow[i];
				if (aiValuesToShow[i] > iMax) iMax = aiValuesToShow[i];
			}
			if (iMin < 0) iMin = 0;
			if (iMax < (iMin + 1)) iMax = iMin + 1;
			int iDiff = iMax - iMin;

			//printf( "t%d b%d l%d r%d\n",rc.top,rc.bottom,rc.left,rc.right );
			HBRUSH hbrush[6];
			hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
			hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
			hbrush[4] = CreateSolidBrush(RGB(0, 0, 255));
			hbrush[5] = CreateSolidBrush(RGB(255, 0, 255));
			RECT rc;
			GetClientRect(hwnd, &rc);
			RECT rect[NUM_RESOURCES];
			for (int i = 0; i < NUM_CLIENTS; i++)
				rect[i] = rc; // Copy original size
			for (int i = 1; i < NUM_CLIENTS; i++)
				rect[i - 1].right = rect[i].left = rc.right * i / NUM_CLIENTS;
			// Fix heights to be relative to total
			int iFullHeight = rc.bottom - rc.top;
			for (int i = 0; i < NUM_CLIENTS; i++)
				rect[i].top = rect[i].bottom - (iFullHeight * aiValuesToShow[i]) / iMax;
			for (int i = 0; i < NUM_CLIENTS; i++)
				FillRect(hdc, &rect[i], hbrush[i % 6]);
			for (int i = 0; i < 6; i++)
				DeleteObject(hbrush[i]); // Free the brush resources
		} // End of draw the background
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_USER + 1:
		iClientValues[wParam - 1]++;
		printf("Clients:\t");
		for (int i = 0; i < NUM_CLIENTS; i++)
		{
			printf("%d  ", iClientValues[i]);
		}
		printf("\n");
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		{
			int aiValuesToShow[NUM_RESOURCES];
			// Todo - copy the values of your resources into the array above
			// Note that this array assumes that resource 1 is in index 0
			for (int i = 0; i < NUM_RESOURCES; i++) // Example only for how I did it
				aiValuesToShow[i] = iResValues[i]; // Example line only - change this
			// Now work out how high to make each bar
			int iMax = -10000000; int iMin = 10000000;
			for (int i = 0; i < 10; i++)
			{
				if (aiValuesToShow[i] < iMin) iMin = aiValuesToShow[i];
				if (aiValuesToShow[i] > iMax) iMax = aiValuesToShow[i];
			}
			if (iMin < 0) iMin = 0;
			if (iMax < (iMin + 1)) iMax = iMin + 1;
			int iDiff = iMax - iMin;

			//printf( "t%d b%d l%d r%d\n",rc.top,rc.bottom,rc.left,rc.right );
			HBRUSH hbrush[6];
			hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
			hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
			hbrush[4] = CreateSolidBrush(RGB(0, 0, 255));
			hbrush[5] = CreateSolidBrush(RGB(255, 0, 255));
			RECT rc;
			GetClientRect(hwnd, &rc);
			RECT rect[NUM_RESOURCES];
			for (int i = 0; i < NUM_RESOURCES; i++)
				rect[i] = rc; // Copy original size
			for (int i = 1; i < NUM_RESOURCES; i++)
				rect[i - 1].right = rect[i].left = rc.right * i / NUM_RESOURCES;
			// Fix heights to be relative to total
			int iFullHeight = rc.bottom - rc.top;
			for (int i = 0; i < NUM_RESOURCES; i++)
				rect[i].top = rect[i].bottom - (iFullHeight * aiValuesToShow[i]) / iMax;
			for (int i = 0; i < NUM_RESOURCES; i++)
				FillRect(hdc, &rect[i], hbrush[i % 6]);
			for (int i = 0; i < 6; i++)
				DeleteObject(hbrush[i]); // Free the brush resources
		} // End of draw the background
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_USER + 2:
		// Only overwrite the value when the new value is larger
		if (iResValues[wParam - 1] < lParam)
			iResValues[wParam - 1] = lParam;
		printf("Resource:\t");
		for (int i = 0; i < NUM_RESOURCES; i++)
		{
			printf("%d  ", iResValues[i]);
		}
		printf("\n");
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

DWORD WINAPI HandleConnection(LPVOID lpParm){
	// Grab the info that was passed in ...
	DataForThread* pDataPassedIn = (DataForThread*)lpParm;
	SOCKET ClientSocket = pDataPassedIn->ClientSocket;
	int iConnectionNumber = pDataPassedIn->iConnectionNumber;
	// And then delete the data that was passed in
	// (We could just keep using it and delete it later but this prevents forgetting to do so)
	free(pDataPassedIn); // Matches the malloc below (search for it if not sure)
	// Now all of our data is on the stack - so will be tidied up for us

	// We have our own buffer for receiving data
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;
	int iReceiveIndex = 0; // Index into struct that we are getting
	WrapperDataClientToServer dataReceived = { 0 };
	// Receive until the peer shuts down the connection
	do
	{
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			for (int i = 0; i < iResult; i++)
			{
				dataReceived.b[iReceiveIndex++] = recvbuf[i];
				if (iReceiveIndex >= sizeof(DataClientToServer))
				{// We have a full message now so do something with it:
					iReceiveIndex = 0; //Go back to start for the next one

					HWND hwnd1 = FindWindow("ThreadProgWindow", NULL);
					HWND hwnd2 = FindWindow("ResourceAccessWindow", NULL);

					if (!hwnd1) {
						printf("Thread Progress Window does not exist.\n");
					}
					else{
						PostMessage(hwnd1, WM_USER + 1, dataReceived.a.clientID, 0);
					}

					if (!hwnd2){
						printf("Resource Access Window does not exist.\n");
					}
					else{
						PostMessage(hwnd2, WM_USER + 2, 7, dataReceived.a.resource7);
						PostMessage(hwnd2, WM_USER + 2, 8, dataReceived.a.resource8);
						PostMessage(hwnd2, WM_USER + 2, 9, dataReceived.a.resource9);
						PostMessage(hwnd2, WM_USER + 2, 10, dataReceived.a.resource10);
						PostMessage(hwnd2, WM_USER + 2, 11, dataReceived.a.resource11);
						PostMessage(hwnd2, WM_USER + 2, 12, dataReceived.a.resource12);
					}
				}
			}
		}
		else if (iResult < 0)
		{
			printf("ClientSocket recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			return 1;
		}
	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("ClientSocket shutdown failed with error: %d\n", WSAGetLastError());
	}

	// cleanup
	closesocket(ClientSocket);
	return 0; // success
}

DWORD WINAPI DoServer(LPVOID lpParm)
{
	WSADATA wsaData;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
	}

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct sockaddr_in localaddress;
	localaddress.sin_family = AF_INET;
	localaddress.sin_addr.s_addr = inet_addr(DEFAULT_ADDR);
	localaddress.sin_port = htons(DEFAULT_PORT);

	// Create a SOCKET for connecting to server
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, (SOCKADDR *)&localaddress, sizeof(localaddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		return 1;
	}

	int iConnectionNumber = 0;

	// wait for incoming connections and accept them as they come in:
	while (TRUE)
	{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			return 1;
		}

		// Allocate some memory to store any data we need to pass to the thread
		DataForThread* p = (DataForThread*)malloc(sizeof(DataForThread));
		p->ClientSocket = ClientSocket; // Socket to get data from
		p->iConnectionNumber = iConnectionNumber + 1; // number of this connection - add 1 to make it 1-based
		// Set any other data that you want to pass as well
		// Note - we assume that the client thread frees the memory - search for free( above this
		iConnectionNumber++;// Next connection will be 1 higher
		// Now create a thread to handle this connection, giving it the connection details
		// Note: calling the function direct would be:  HandleConnection( (LPVOID)p ); 
		HANDLE h = CreateThread(NULL, 0, HandleConnection, p, 0, NULL);
		CloseHandle(h); // We no longer need the handle to the thread - it is on its own
	}

	// Close down windows sockets
	WSACleanup();
	return 0;
}

int main()
{
	printf("Server starting at PORT:%d...\n", DEFAULT_PORT);
	HANDLE h = CreateThread(NULL, 0, DoServer, NULL, 0, NULL);
	CloseHandle(h); // We no longer need the handle to the thread - it is on its own

	//Register the thread process window
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc1;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "ThreadProgWindow";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//Create the thread process window
	HWND hwnd1 = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"ThreadProgWindow",
		"Thread Progress window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 480,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hwnd1 == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Set position to not overlap the other one
	SetWindowPos(hwnd1, HWND_TOPMOST, 0, 50, 0, 0, SWP_NOSIZE);
	ShowWindow(hwnd1, SW_SHOW);
	UpdateWindow(hwnd1);

	// Register the resource access window
	WNDCLASSEX wc2;
	wc2.cbSize = sizeof(WNDCLASSEX);
	wc2.style = 0;
	wc2.lpfnWndProc = WndProc2; // CHANGES
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = GetModuleHandle(NULL);
	wc2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc2.lpszMenuName = NULL;
	wc2.lpszClassName = "ResourceAccessWindow";
	wc2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc2))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Create the resource access window
	HWND hwnd2 = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"ResourceAccessWindow",
		"Resource Access window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 480,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hwnd2 == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Set position to not overlap the other one
	SetWindowPos(hwnd2, HWND_TOPMOST, 360, 50, 0, 0, SWP_NOSIZE);
	ShowWindow(hwnd2, SW_SHOW);
	UpdateWindow(hwnd2);

	// Only need one message loop - it will handle messages for both windows
	// calling the appropriate window procedure

	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
