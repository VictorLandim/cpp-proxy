#include "application.hpp"
#include "proxyServer.hpp"
#include "request.hpp"
#include "utils.hpp"

void Application::run()
{
	ProxyServer* proxyServer = new ProxyServer(8080);

	proxyServer->setupListen();
	proxyServer->acceptConnection(); // waits for connection

	std::string serverResponse = proxyServer->clientRequest;

	Request* request = new Request(serverResponse);

	std::cout << "Browser request:" << std::endl << request->content << std::endl;

	//std::map<std::string, std::string> response = Utils::parseRequest(serverResponse);

	//for (auto itr = response.begin(); itr != response.end(); ++itr) {
	//	std::cout << "Key: " << itr->first << std::endl;
	//	std::cout << "Value: " << itr->second << std::endl;
	//}

	std::string hostResponse = proxyServer->makeRemoteRequest(request->content, request->host);

	std::cout << "Host response:" << std::endl << hostResponse << std::endl;

	proxyServer->respond(hostResponse);
	

	delete request;
	delete proxyServer;
}