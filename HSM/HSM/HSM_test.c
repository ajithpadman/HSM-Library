#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_
#include "hsm_test.h"
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windows.h>
#define BUF_SIZE 255
#define DEFAULT_BUFLEN 512
#pragma comment(lib,"ws2_32.lib") //Winsock Library

const char statelist[10][20]={"NULLSTATE","ROOT_STATE","STATE_1","STATE1_1","STATE1_2","STATE_2","STATE2_1","STATE2_1_1","STATE_3","State4"};
const char eventlist[7][20]={"EV_NULL","EV_DEFAULT","EV2","EV_1","EV5","EV3","EV4"};
DWORD WINAPI Telnethandler( LPVOID lpParam );
void ErrorHandler(LPTSTR lpszFunction);


int main()
{
	DWORD   dwThreadIdArray;//[MAX_THREADS];
	HANDLE  hThreadArray;//[MAX_THREADS];
	SampleHSM_HSM_Create();
	SampleHSM_HSM_Start();
	hThreadArray = CreateThread( 
		NULL,                   // default security attributes
		0,                      // use default stack size  
		Telnethandler,       // thread function name
		0           ,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray);   // returns the thread identifier 
	// Check the return value for success.
	// If CreateThread fails, terminate execution. 
	// This will automatically clean up threads and memory. 

	if (hThreadArray == NULL) 
	{
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);
	}
	// Wait until all threads have terminated.
	WaitForMultipleObjects(1, &hThreadArray, TRUE, INFINITE);
	// Close all thread handles and free memory allocations.
	CloseHandle(&hThreadArray);
	return 0;
}
DWORD WINAPI Telnethandler( LPVOID lpParam ) 
{ 
	
	int eventID = 0;
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	char message[10];
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	printf("Initialised.\n");
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(0);
	}

	puts("Bind done");

	//Listen to incoming connections
	listen(s , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);

	if( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
	{
		puts("Connection accepted");

		//Reply to the client
		sprintf(message, "%d", SampleHSM_hsm_getCurrentState());

		send(new_socket , message , strlen(message) , 0);
		do {

			iResult = recv(new_socket, recvbuf, recvbuflen, 0);
			if ( iResult > 0 )
			{
				recvbuf[iResult] = 0;
				printf("Data received: %s\n", recvbuf);
				fireEvent(atoi(recvbuf));
				sprintf(message, "%d", SampleHSM_hsm_getCurrentState());
				send(new_socket , message , strlen(message) , 0);
			}


			else if ( iResult == 0 )
				printf("Connection closed\n");
			else
				printf("recv failed: %d\n", WSAGetLastError());

		} while( iResult > 0 );
	}


	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
		return 1;
	}

	closesocket(s);
	WSACleanup();

	return 0;
} 
void fireEvent(int eventID)
{
	if(eventID <= MAX_EVENTS)
	{
		printf("Current State %s\n\n",statelist[SampleHSM_hsm_getCurrentState()]);
		printf("Firing Event %s\n",eventlist[eventID]);
		SampleHSM_HSM_onEvent((EventID)eventID);
		printf("Current State  After event%d is %s\n\n",eventID,statelist[SampleHSM_hsm_getCurrentState()]);
	}
	else
	{
		printf("Specified Not Event Found");
	}
}

void ErrorHandler(LPTSTR lpszFunction) 
{ 
	// Retrieve the system error message for the last-error code.

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message.
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40) * sizeof(TCHAR)); 
	// Free error-handling buffer allocations.
	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

