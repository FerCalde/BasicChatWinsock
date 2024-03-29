#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

static bool bDebugMsg = true;

void printLogs(bool* _bDebugMsg, const char* _msg);
void printLogs(const char* _msg);


int main()
{
	//Initialize
	WSADATA xWsa;
	WSAStartup(MAKEWORD(2, 2), &xWsa);
	printLogs("Client: Initialize Lib 'WSA'");

	//Create Socket
	SOCKET xSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	xSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (xSocket == INVALID_SOCKET)
	{
		printLogs("ERROR! *** Client: Create Socket Failed");
		//printf("Error: %d\n", WSAGetLastError());
		return -1;
	}
	printLogs("Client: Create Socket!");
	//char sBufferServerIp[20]{'\0'};
	//std::cout << "Client: enter a Ip to Connect: ";
	//std::cin >> sBufferServerIp;
	//std::cout << sBufferServerIp;
	//Connect to Server
	struct sockaddr_in xSockAddr;
	xSockAddr.sin_family = AF_INET;
	xSockAddr.sin_port = htons(9999); //DEBE SER MISMO PUERTO QUE EN SERVER!
	inet_pton(AF_INET, "127.0.0.1"/*sBufferServerIp*/, &(xSockAddr.sin_addr)); //Conectar a esta IP! 
															//En Actualizacion se pedir� al usuario meter la IP a la cual se quiere conectar
	memset(xSockAddr.sin_zero, 0, 8);
	
	int iConnection = connect(xSocket, (SOCKADDR*)&xSockAddr, sizeof(sockaddr));
	if (iConnection == -1)
	{
		printLogs("ERROR! *** Client: Connect Failed!");
		return -1;
	}
	printLogs("Client: Correct Connect with Server!");

	//Send Messages
	char sBuffer[1024];
	int iLen = 0;
	do
	{
		std::cout << "(Client) text to send (\"exit\" to close the app): ";
		//std::cin >> sBuffer;
		fgets(sBuffer, 1023, stdin);
		
		iLen = send(xSocket, sBuffer, strlen(sBuffer), 0);
		if (iLen == -1)
		{
			printLogs("ERROR! *** Client: Send Failed!");
			return -1;
		}
		/*else
		{
			printLogs("INFO! *** Client: Send Successful!");
		}*/
		
	} while (iLen !=-1 && strcmp(sBuffer, "exit") != 0);

	closesocket(xSocket); //Close Socket
	return 0;
}

void printLogs(bool* _bDebugMsg, const char* _msg)
{
	if (_bDebugMsg)
	{
		std::cout << "\n\n" << _msg << "\n\n";
	}

}
void printLogs(const char* _msg)
{
	if (bDebugMsg)
	{
		std::cout << "\n\n" << _msg << "\n\n";
	}
}