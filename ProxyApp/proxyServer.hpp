#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "request.hpp"
#include "response.hpp"

#pragma comment (lib, "ws2_32.lib")

class ProxyServer{
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
	Request* request;
	Response* response;

	ProxyServer();
	ProxyServer(int port);
	~ProxyServer();

	void setupListen();
	void acceptConnection();
	void respond(std::string);
	void closeClientSocket();

	void makeRemoteRequest(std::string, std::string);
};