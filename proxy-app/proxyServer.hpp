#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

class ProxyServer {
private:
	WSADATA wsData;

	int port;

	SOCKET serverSocket;
	sockaddr_in serverSocketHint;

	SOCKET clientSocket;
	sockaddr_in clientSocketHint;

	void init();
	void cleanUp();

public:
	std::string clientRequest; // request string made by the browser

	ProxyServer(int port);
	~ProxyServer();

	void setupListen();
	void acceptConnection();
	void respond(std::string);
	std::string makeRemoteRequest(std::string, std::string);
};