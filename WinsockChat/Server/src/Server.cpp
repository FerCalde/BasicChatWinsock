#include <iostream>
#include <WinSock2.h>
#include <stdio.h>

static bool bDebugMsg = true;

void printLogs(bool* _bDebugMsg, const char* _msg);
void printLogs(const char* _msg);
void printReceiveMsg(const char* _msg);

int main()
{
	//Initialize
	WSADATA xWsa;
	WSAStartup(MAKEWORD(2, 0), &xWsa);
	printLogs(&bDebugMsg, "Server: Initialize Lib 'WSA'");

	//Create Socket
	SOCKET xSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (xSocket == INVALID_SOCKET)
	{
		printLogs("ERROR! *** Server: Create Socket Failed");
		return -1;
	}
	
	//Struct for local address
	struct sockaddr_in xLocal;
	xLocal.sin_family = AF_INET;
	xLocal.sin_addr.s_addr = INADDR_ANY;
	xLocal.sin_port = htons(9999);
	memset(xLocal.sin_zero, 0, 8); //Zero the rest of the struct. We need 16bytes

								   //Bind the Socket to the LocalAddres
	if (bind(xSocket, (SOCKADDR*)&xLocal, sizeof(xLocal)) == -1)
	{
		printLogs(&bDebugMsg, "Server: Binding error!");
		
		return -1;
	}

	//Specificate the Listening Connections that are available for the Socket
	//if(listen(xSocket, SOMAXCONN) == -1)
	if(listen(xSocket, 1) == -1)
	{
		printLogs("Server: Listening error!");
		return -1;
	}
	
	printLogs("Server: Waiting Connection...");

	/****
		*devuelve el socket con el que comunicar con el nuevo cliente conectado en el momento que se hace el accept
		*Reaprovecho el adress de xLocal para guardar el address del cliente que se conecta
	**/
	int iLen = sizeof(sockaddr);
	xSocket = accept(xSocket, (sockaddr*)&xLocal, &iLen);

	printLogs("Server: Client Connected!");
	printLogs("Server: Ready to Receive text!");
	
	//Receive text
	char sBuffer[1024];
	do
	{
		iLen = recv(xSocket, sBuffer, 1023, 0);
		if (iLen > 0)
		{
			sBuffer[iLen] = '\0';
			printReceiveMsg(sBuffer);
		}
		else
		{
			printLogs( "Server: Client Disconnected!");
			break;
		}
		
	} while (iLen>0 && strcmp(sBuffer, "exit") != 0);
	
	closesocket(xSocket);

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

void printReceiveMsg(const char* _msg)
{
	if (bDebugMsg)
	{
		std::cout << "\nServer:\n\tReceived text : " << _msg << "\n";
	}
}