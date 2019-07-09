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

	SOCKET serverSocket;
	sockaddr_in serverSocketHint;

	SOCKET clientSocket;
	sockaddr_in clientSocketHint;

public:
	int port;

	Request* request;
	Response* response;

	ProxyServer();
	~ProxyServer();

	void init(int port);

	void cleanUp();

	void setupListen();
	void acceptConnection();
	void respond(std::string);
	void closeClientSocket();

	void makeRemoteRequest(std::string, std::string);
};