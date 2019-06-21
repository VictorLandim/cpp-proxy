#include "serverThread.hpp"
#include "proxyServer.hpp"
#include "request.hpp"

ServerThread::ServerThread(QObject* parent) : QThread(parent)
{
}

void ServerThread::run()
{
	ProxyServer* proxyServer = new ProxyServer(8080);
	std::cout << "> Proxy server listening to connections." << std::endl;
	emit statusChanged("Proxy server is listening to connections.");

	forever
	{
		if (shouldListen)
		{
			proxyServer->setupListen();
			proxyServer->acceptConnection(); // waits for connection

			printClientRequest(proxyServer->request->toString());

			emit requestReceived(QString::fromStdString(proxyServer->request->toString()));

			shouldListen = false;
		}

		if (shouldRequestToServer)
		{

			std::cout << "> Requesting " << proxyServer->request->path << "." << std::endl;

			proxyServer->makeRemoteRequest(proxyServer->request->toString(), proxyServer->request->host);

			printHostResponse(proxyServer->response->body);

			emit responseReceived(QString::fromStdString(proxyServer->response->body));

			shouldRequestToServer = false;
		}
		
		if (shouldRespondToClient)
		{

			proxyServer->respond(proxyServer->response->body);
			proxyServer->closeClientSocket();
			
			shouldRespondToClient = false;
			shouldListen = true;
		}

		std::cout << "----------------------------------------" << std::endl;

		msleep(1000);
	}

	delete proxyServer;
}

void ServerThread::printClientRequest(std::string request)
{
	std::cout << "========== PARSED BROWSER REQUEST START ==========" << std::endl <<
		request << std::endl <<
		"========== BROWSER REQUEST END ==========" << std::endl;

}

void ServerThread::printHostResponse(std::string response)
{
	std::cout << "========== HOST RESPONSE START ==========" << std::endl <<
		response << std::endl <<
		"========== HOST RESPONSE END ==========" << std::endl;
}

// slots
void ServerThread::setShouldListen() { shouldListen = true; }
void ServerThread::setShouldRequestToServer() { shouldRequestToServer = true; }
void ServerThread::setShouldRespondToClient() { shouldRespondToClient = true; }