#include "serverThread.hpp"

ServerThread::ServerThread(QObject* parent, int port) : QThread(parent)
{
	proxyServer = new ProxyServer();
}

void ServerThread::run()
{
	forever
	{
		if (shouldListen)
		{
			try {
				proxyServer->setupListen();
				proxyServer->acceptConnection(); // blocked: waits for connection

				printClientRequest(proxyServer->request->toString());

				emit requestReceived(QString::fromStdString(proxyServer->request->toString()));

				shouldListen = false;
			}
			catch (std::exception& e) 
			{
				proxyServer->closeClientSocket();
				std::cout << "# Error: " << e.what() << std::endl;
			}
		}

		if (shouldRequestToServer)
		{
			try {
				std::cout << "> Requesting " << proxyServer->request->path << "." << std::endl;

				proxyServer->makeRemoteRequest(finalRequest, proxyServer->request->host);

				printHostResponse(proxyServer->response->toString());

				emit responseReceived(QString::fromStdString(proxyServer->response->toString()));

				shouldRequestToServer = false;
			}
			catch (std::exception& e)
			{
				std::cout << "# Error: " << e.what() << std::endl;
				shouldRequestToServer = false;
			}
		}
		
		if (shouldRespondToClient)
		{
			try {

				proxyServer->respond(finalResponse);
				proxyServer->closeClientSocket();

				shouldRespondToClient = false;
				shouldListen = true;
			}
			catch (std::exception& e)
			{
				std::cout << "# Error: " << e.what() << std::endl;
				shouldRespondToClient = false;
			}
		}

		//std::cout << ".\r" << std::endl;
		//std::cout << "----------------------------------------" << std::endl;
		//msleep(1000);
	}

	delete proxyServer;
}

void ServerThread::printClientRequest(std::string request)
{
	std::cout << "========== PARSED BROWSER REQUEST START ==========" << std::endl <<
		request << std::endl <<
		"==========  PARSED BROWSER REQUEST END ==========" << std::endl;
}

void ServerThread::printHostResponse(std::string response)
{
	std::cout << "========== HOST RESPONSE START ==========" << std::endl <<
		response << std::endl <<
		"========== HOST RESPONSE END ==========" << std::endl;
}

// slots
void ServerThread::setShouldListen() { shouldListen = true; }

void ServerThread::setListeningPort(int port)
{
	proxyServer->init(port);
	std::string message = "Proxy server is listening on port " + std::to_string(proxyServer->port) + ".";
	std::cout << "> " << message << std::endl;
	emit statusChanged(QString::fromStdString(message));

}

void ServerThread::setRequest(QString request)
{
	finalRequest = request.toStdString();
	shouldRequestToServer = true;
}

void ServerThread::setResponse(QString response)
{
	finalResponse = response.toStdString();
	shouldRespondToClient = true;
}