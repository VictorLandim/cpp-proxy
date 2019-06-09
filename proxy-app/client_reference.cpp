#include <iostream>
#include <string>
#include <WS2tcpip.h>

#define IP 127.0.0.1
#define PORT 80

void mai_n()
{
	// server info
	std::string ipAddress = "172.217.162.174";
	int port = 80;

	// init winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &data);

	if (wsOk != 0)
	{
		std::cerr << "Can't start winsock." << std::endl;
		return;
	}

	// create socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Can't create client socket." << std::endl;
		WSACleanup();
		return;
	}

	// fill hint struct
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	
	// connect to server
	int connResult = connect(clientSocket, (sockaddr*)& hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server." << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return;
	}

	// do-while loop to send and receive data
	char buf[4096];
	std::string userInput;

	do
	{
		// prompt the user for some text
		std::cout << "> ";
		getline(std::cin, userInput);
		
		// make sure the user has typed something
		if (userInput.size() > 0)
		{
			// send the text
			int sendResult = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);

			if (sendResult != SOCKET_ERROR)
			{
				// wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(clientSocket, buf, 4096, 0);
				
				if (bytesReceived > 0)
				{
					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
				}
			}
		}

		// echo to console
	} while (userInput.size() > 0);


	// gracefully close down everything
	closesocket(clientSocket);
	WSACleanup();

	system("pause");
}