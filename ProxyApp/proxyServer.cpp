#include "proxyServer.hpp"

ProxyServer::ProxyServer()
{
	// default port;
	//init(8080);

	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		throw std::exception("Can't Initialize winsock.");
	}

	std::cout << "> Winsock initialized." << std::endl;
}

void ProxyServer::init(int port)
{
	// reset sockets 
	closesocket(clientSocket);
	closesocket(serverSocket);

	this->port = port;
	request = new Request();
	response = new Response();
}

void ProxyServer::setupListen()
{
	// Create server listening socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Can't create server socket.");
	}

	// Bind the ip address and port to a socket
	serverSocketHint.sin_family = AF_INET;
	serverSocketHint.sin_port = htons(port);
	serverSocketHint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(serverSocket, (sockaddr*)& serverSocketHint, sizeof(serverSocketHint));

	// Tell Winsock the socket is for listening 
	listen(serverSocket, SOMAXCONN);
}

void ProxyServer::acceptConnection()
{
	// Wait for a connection
	int clientSize = sizeof(clientSocketHint);

	// blocks until clients connects
	clientSocket = accept(serverSocket, (sockaddr*)& clientSocketHint, &clientSize);

	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	// resolve clients name & port
	if (getnameinfo((sockaddr*)& clientSocketHint, sizeof(clientSocketHint), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << "> " << host << " connected on port " << service << "." << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &clientSocketHint.sin_addr, host, NI_MAXHOST);
		std::cout << "> " << host << " connected on port " <<
			ntohs(clientSocketHint.sin_port) << "." << std::endl;
	}

	// Close listening socket
	closesocket(serverSocket);

	char buffer[4096];
	std::string clientRequest;

	// While loop: accept and store message
	while (true)
	{
		ZeroMemory(buffer, sizeof(buffer));

		// Wait for client to send data
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (bytesReceived == SOCKET_ERROR)
		{
			throw std::exception("Error in recv().");
		}

		if (bytesReceived == 0)
		{
			std::cout << "> Client disconnected." << std::endl;
			break;
		}

		clientRequest.append(buffer);

		// TODO: IMPROVE

		request->parse(clientRequest);
		break;
	}
}

void ProxyServer::respond(std::string data)
{
	// Echo message back to client
	send(clientSocket, data.c_str(), data.size() + 1, 0);
	//send(clientSocket, dataBuffer, bytesReceived + 1, 0);
}

void ProxyServer::makeRemoteRequest(std::string request, std::string host)
{
	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it, that we are looking for a IPv4 TCP Connection.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

	// Aquiring of the IPv4 address of a host using the newer
	// "getaddrinfo" function which outdated "gethostbyname".
	// It will search for IPv4 addresses using the TCP-Protocol.
	struct addrinfo* targetAdressInfo = NULL;
	DWORD getAddrRes = getaddrinfo(host.c_str(), NULL, &hints, &targetAdressInfo);
	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		throw std::exception("Could not resolve the host name.");
	}

	// Create the Socket Address Informations, using IPv4
	// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*) targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(80);  // HTTP Port: 80

	// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
	{
		throw std::exception("Could not create socket to host.");
	}

	// Establishing a connection to the web Socket
	std::cout << "> Connecting to " << host << "." << std::endl;
	if (connect(webSocket, (SOCKADDR*)& sockAddr, sizeof(sockAddr)) != 0)
	{
		closesocket(webSocket);
		std::string errorMessage = "Could not connect to " + host + ".";
		throw std::exception(errorMessage.c_str());
	}

	std::cout << "> Connection established." << std::endl;

	// Sending a HTTP-GET-Request to the Web Server
	int sentBytes = send(webSocket, request.c_str(), strlen(request.c_str()), 0);
	if (sentBytes < strlen(request.c_str()) || sentBytes == SOCKET_ERROR)
	{
		closesocket(webSocket);
		throw std::exception("Could not send the request to the server.");
	}

	char buffer[4096];
	std::string serverResponse;

	while(true)
	{
		ZeroMemory(buffer, sizeof(buffer));

		// Wait for client to send data
		int bytesReceived = recv(webSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			throw std::exception("Error in recv().");
		}

		if (bytesReceived == 0)
		{
			std::cout << "> Host disconnected." << std::endl;
			break;
		}

		serverResponse.append(buffer);
	}

	closesocket(webSocket);

	std::cout << "> Host response fetched." << std::endl;

	// TODO
	//response->body = serverResponse;
	response->parse(serverResponse);
}

void ProxyServer::cleanUp()
{
	// Close the sockets
	closesocket(clientSocket);
	closesocket(serverSocket);

	// Cleanup winsock
	WSACleanup();
}

void ProxyServer::closeClientSocket()
{
	closesocket(clientSocket);
}

ProxyServer::~ProxyServer()
{
	delete request;
	delete response;
	cleanUp();
}